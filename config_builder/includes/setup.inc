<?php
/**
 * @file
 * Setup module integration.
 */

/**
 * Implements hook_setup_info().
 */
function config_builder_setup_info() {
  $types = array();

  $types['config_builder'] = array(
    'form callback' => 'config_builder_setup_config_builder_form_callback',
    'finish callback' => 'config_builder_setup_config_builder_finish_callback',
  );

  return $types;
}

/**
 * Form callback for 'config_builder' method.
 */
function config_builder_setup_config_builder_form_callback($form, &$form_state) {
  if (isset($form_state['setup_step']['name'])) {
    $config = config_builder_crud_load($form_state['setup_step']['name']);
    if ($config) {
      // Set default value on each item.
      _config_builder_recurse_defaults($config->fapi);

      $form += $config->fapi;
    }
  }

  return $form;
}

/**
 * Finish callback for 'config_builder' method.
 */
function config_builder_setup_config_builder_finish_callback(&$form_state) {
  system_settings_form_submit(array(), $form_state);
  theme('status_messages');
}
