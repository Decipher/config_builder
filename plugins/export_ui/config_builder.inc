<?php
/**
 * @file
 * CTools Export UI plugin for Configuration Builder pages.
 */

/**
 * CTools Export UI required function for plugin definition
 */
function config_builder_config_builder_ctools_export_ui() {
  return array(
    'schema' => 'config_builder',
    'access' => 'administer config builder',

    'menu' => array(
      'menu prefix' => 'admin/structure',
      'menu item' => 'config_builder',
      'menu title' => 'Configuration builder',
      'menu description' => 'Administer Configuration pages.',
    ),

    'title singular' => t('configuration page'),
    'title singular proper' => t('Configuration page'),
    'title plural' => t('configuration pages'),
    'title plural proper' => t('Configuration pages'),

    'handler' => 'config_builder_ui',

    'form' => array(
      'settings' => 'config_builder_export_ui_form',
      'submit' => 'config_builder_export_ui_form_submit',
    ),

    'export' => array(
      'admin_title' => 'label',
      'admin_description' => 'description',
    ),
  );
}

/**
 * Configuration Builder settings form.
 */
function config_builder_export_ui_form(&$form, &$form_state) {
  $item = $form_state['item'];

  // Basic information fieldset.
  $form['info']['#title'] = t('Basic information');
  $form['info']['#type'] = 'fieldset';
  $form['info']['#collapsible'] = TRUE;
  $form['info']['#collapsed'] = $form_state['op'] != 'add';

  // Page settings.
  $form['page'] = array(
    '#type' => 'fieldset',
    '#title' => t('Page settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['page']['path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path'),
    '#field_prefix' => $GLOBALS['base_url'] . base_path(),
    '#default_value' => $item->path,
    '#required' => TRUE,
  );

  // Form builder.
  $form['form_builder_id'] = array(
    '#type' => 'hidden',
    '#value' => isset($form_state['input']['form_builder_id'])
      ? $form_state['input']['form_builder_id']
      : drupal_substr(md5(REQUEST_TIME . rand(1000, 9999)), 0, 32)
  );

  module_load_include('inc', 'form_builder', 'includes/form_builder.admin');
  module_load_include('inc', 'form_builder', 'includes/form_builder.api');
  module_load_include('inc', 'form_builder', 'includes/form_builder.cache');

  $form_type = 'config_builder';
  $form_id = $form['form_builder_id']['#value'];

  // Set the current form type (used for display of the sidebar block).
  form_builder_active_form($form_type, $form_id);

  // Load the current state of the form.
  $form_structure = _config_builder_form_builder_load_form($item, $form_id);

  $form['fapi'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings form'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['fapi']['form_builder'] = form_builder_preview($form, $form_state, $form_structure, $form_type, $form_id);

  $form['buttons']['edit'] = array(
    '#type' => 'submit',
    '#value' => t('Save & Edit'),
  );
}

/**
 * Submit callback for Custom Formatters settings form.
 */
function config_builder_export_ui_form_submit(&$form, &$form_state) {
  module_load_include('inc', 'form_builder', 'includes/form_builder.admin');
  module_load_include('inc', 'form_builder', 'includes/form_builder.api');
  module_load_include('inc', 'form_builder', 'includes/form_builder.cache');

  // @TODO - Reproduce this functionality or require form_builder_examples.module.
  include drupal_get_path('module', 'form_builder') . '/examples/form_builder_examples.module';

  $form_id = drupal_substr($form['form_build_id']['#value'], 0, 32);
  $form_cache = form_builder_cache_load('config_builder', $form_id);

  if (is_array($form_cache)) {
    $form_state['item']->fapi = form_builder_examples_export_recurse($form_cache);
    $form_state['values']['fapi'] = $form_state['item']->fapi;
  }

  // Remove the cached form_builder form.
  form_builder_cache_delete('config_builder', $form_id);

  // Rebuild the Configuration builder index.
  form_builder_crud_index_save((object) $form_state['values']);

  // Flush all caches.
  variable_set('menu_rebuild_needed', TRUE);
  drupal_flush_all_caches();

  if ($form_state['values']['op'] == t('Save & Edit')) {
    $destination = "admin/structure/config_builder/list/{$form_state['values']['name']}/edit";
    $_GET['destination'] = isset($_GET['destination']) ? "{$destination}?destination={$_GET['destination']}" : $destination;
  }
}
