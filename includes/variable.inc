<?php
/**
 * @file
 * Variable module integration.
 */

/**
 * Implements hook_config_builder_module_implements_alter() on behalf of
 * variable.module.
 */
function variable_config_builder_module_implements_alter(&$implementations, $hook) {
  if ('variable_info_alter' == $hook) {
    unset($implementations['config_builder']);
    $implementations['config_builder'] = FALSE;
  }
}

/**
 * Implements hook_variable_info_alter().
 */
function config_builder_variable_info_alter(&$variables, $options) {
  foreach (config_builder_crud_index_load_all() as $index) {
    if (!isset($variables[$index->id])) {
      $variables[$index->id] = array(
        'title' => $index->title,
        'type' => _config_builder_variable_type_map($index->type),
        'group' => 'config_builder',
        'module' => 'config_builder',
      );
    }
  }
}

/**
 * Helper function; returns variable type from form buider type.
 */
function _config_builder_variable_type_map($type) {
  $map = array(
    'textfield' => 'string',
  );

  return isset($map[$type]) ? $map[$type] : 'unknown';
}

/**
 * Implements hook_variable_group_info().
 */
function hook_variable_group_info() {
  $groups = array();

  $groups['config_builder'] = array(
    'title' => t('Configuration builder'),
    // 'description' => t('Site information and maintenance mode'),
    // 'access' => 'administer site configuration',
    // 'path' => array('admin/config/system/site-information', 'admin/config/development/maintenance'),
  );

  return $groups;
}

/**
 * Implements hook_config_builder_form_builder_types_alter() on behalf of
 * variable.module.
 */
function variable_config_builder_form_builder_types_alter(&$fields) {
  $fields['variable_form_element'] = array(
    'title' => t('Variable'),
    'properties' => array(
      'variable',
    ),
    'default' => array(
      '#type' => 'variable_form_element',
    ),
  );
}

/**
 * Implements hook_config_builder_form_builder_properties_alter() on behalf of
 * variable.module.
 */
function variable_config_builder_form_builder_properties_alter(&$properties, $form_type) {
  if ('config_builder' == $form_type) {
    $properties['variable'] = array(
      'form' => 'config_builder_property_variable_form_element_form',
    );
  }
}

/**
 * Configuration form for the "variable" property.
 */
function config_builder_property_variable_form_element_form(&$form_state, $form_type, $element, $property) {
  $form = array();

  $variables = array();
  $module_info = system_get_info('module');
  foreach (variable_get_info() as $name => $variable) {
    if (!isset($variables[$module_info[$variable['module']]['name']])) {
      $variables[$module_info[$variable['module']]['name']] = array();
    }
    $variables[$module_info[$variable['module']]['name']][$name] = $variable['title'];
  }
  ksort($variables);

  $form['variable'] = array(
    '#title' => t('Variable'),
    '#type' => 'select',
    '#options' => $variables,
    '#default_value' => $element['#variable'],
    '#required' => TRUE,
  );

  return $form;
}
