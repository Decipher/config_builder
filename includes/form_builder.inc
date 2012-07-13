<?php
/**
 * @file
 * Form Builder module integration.
 */

/**
 * Load Form Builder form.
 */
function _config_builder_form_builder_load_form($config, $form_id) {
  $form = form_builder_cache_load('config_builder', $form_id);

  if ($form === FALSE) {
    $form = array();

    if (!empty($config->name) && isset($config->fapi)) {
      ob_start();
      eval($config->fapi);
      ob_get_clean();

      if (isset($form)) {
        foreach ($form as $key => &$element) {
          $element['#key'] = $key;
          $element['#form_builder'] = array(
            'element_id' => $key,
            'element_type' => $element['#type'],
            'configurable' => TRUE,
            'removable' => TRUE,
          );
        }
      }
      form_builder_cache_save('config_builder', $form_id, $form);
    }
  }

  return $form;
}

/**
 * Implements hook_form_builder_types().
 */
function config_builder_form_builder_types() {
  $fields = array();

  $fields['select'] = array(
    'title' => t('Select list'),
    'properties' => array(
      'title',
      'description',
      'default_value',
      'required',
      'options',
      'multiple', // Handled by options element.
      'key_type', // Handled by options element.
      'key_type_toggle', // Handled by options element.
      'key_type_toggled', // Handled by options element.
      'key',
    ),
    'default' => array(
      '#title' => t('New select list'),
      '#type' => 'select',
      '#options' => array(
        '1' => 'one',
        '2' => 'two',
        '3' => 'three'
      ),
      '#default_value' => array(),
      '#multiple_toggle' => TRUE,
    ),
  );

  $fields['checkboxes'] = array(
    'title' => t('Checkboxes'),
    'properties' => array(
      'title',
      'description',
      'default_value',
      'required',
      'options',
      'multiple',
      'key_type', // Handled by options element.
      'key_type_toggle', // Handled by options element.
      'key_type_toggled', // Handled by options element.
      'key',
    ),
    'default' => array(
      '#title' => t('New checkboxes'),
      '#type' => 'checkboxes',
      '#options' => array(
        'one' => 'one',
        'two' => 'two',
        'three' => 'three'
      ),
      '#default_value' => array(),
    ),
  );

  $fields['radios'] = array(
    'title' => t('Radios'),
    'properties' => array(
      'title',
      'description',
      'default_value',
      'required',
      'options',
      'key_type', // Handled by options element.
      'key_type_toggle', // Handled by options element.
      'key_type_toggled', // Handled by options element.
      'key',
    ),
    'default' => array(
      '#title' => t('New radios'),
      '#type' => 'radios',
      '#options' => array(
        'one' => 'one',
        'two' => 'two',
        'three' => 'three'
      ),
      '#default_value' => array(),
    ),
  );

  $fields['textfield'] = array(
    'title' => t('Textfield'),
    'properties' => array(
      'title',
      'description',
      'field_prefix',
      'field_suffix',
      'default_value',
      'required',
      'size',
      'key',
    ),
    'default' => array(
      '#title' => t('New textfield'),
      '#type' => 'textfield',
      '#default_value' => '',
    ),
  );

  $fields['textarea'] = array(
    'title' => t('Textarea'),
    'properties' => array(
      'title',
      'description',
      'default_value',
      'required',
      'rows',
      'cols',
      'key',
    ),
    'default' => array(
      '#title' => t('New textarea'),
      '#type' => 'textarea',
      '#default_value' => '',
    ),
  );

  // Allow other modules to modify the fields.
  drupal_alter('config_builder_form_builder_types', $fields);

  return array(
    'config_builder' => $fields
  );
}