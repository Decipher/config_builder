<?php

/**
 * @file
 * Form Builder module integration.
 */

/**
 * Load Form Builder form.
 *
 * @param $config
 * @param $form_id
 *
 * @return mixed
 */
function _config_builder_form_builder_load_form($config, $form_id) {
  $loader = FormBuilderLoader::instance();
  $form   = $loader->fromCache('config_builder', $form_id);

  if ($form === FALSE) {
    $form = $loader->fromStorage('config_builder', $form_id);

    if (!empty($config->name) && isset($config->fapi)) {
      $form_array = is_array($config->fapi) ? $config->fapi : array();
      $form_array += $form->getFormArray();
      _config_builder_form_builder_prepare_element_recurse($form_array);
      $form = FormBuilderFormBase::fromArray($form_array);
    }
    $form->save();
  }

  return $form;
}

/**
 * Recursively prepare form builder element.
 *
 * @param $form
 */
function _config_builder_form_builder_prepare_element_recurse(&$form) {
  foreach (element_children($form) as $key) {
    $form[$key]['#key']          = $key;
    $form[$key]['#form_builder'] = array(
      'element_id'   => $key,
      'element_type' => $form[$key]['#type'],
      'configurable' => TRUE,
      'removable'    => TRUE,
    );
    _config_builder_form_builder_prepare_element_recurse($form[$key]);
  }
}

/**
 * Implements hook_form_builder_types().
 */
function config_builder_form_builder_types() {
  $fields = array();

  $fields['fieldset'] = array(
    'title'      => t('Fieldset'),
    'properties' => array(
      'title',
      'description',
      'collapsible',
      'collapsed',
      'key',
      'tree',
    ),
    'default'    => array(
      '#title'       => t('New fieldset'),
      '#type'        => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed'   => FALSE,
    ),
  );

  $fields['select'] = array(
    'title'      => t('Select list'),
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
    'default'    => array(
      '#title'           => t('New select list'),
      '#type'            => 'select',
      '#options'         => array(
        '1' => 'one',
        '2' => 'two',
        '3' => 'three'
      ),
      '#default_value'   => array(),
      '#multiple_toggle' => TRUE,
    ),
  );

  $fields['checkboxes'] = array(
    'title'      => t('Checkboxes'),
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
    'default'    => array(
      '#title'         => t('New checkboxes'),
      '#type'          => 'checkboxes',
      '#options'       => array(
        'one'   => 'one',
        'two'   => 'two',
        'three' => 'three'
      ),
      '#default_value' => array(),
    ),
  );

  $fields['radios'] = array(
    'title'      => t('Radios'),
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
    'default'    => array(
      '#title'         => t('New radios'),
      '#type'          => 'radios',
      '#options'       => array(
        'one'   => 'one',
        'two'   => 'two',
        'three' => 'three'
      ),
      '#default_value' => array(),
    ),
  );

  $fields['textfield'] = array(
    'title'      => t('Textfield'),
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
    'default'    => array(
      '#title'         => t('New textfield'),
      '#type'          => 'textfield',
      '#default_value' => '',
    ),
  );

  $fields['textarea'] = array(
    'title'      => t('Textarea'),
    'properties' => array(
      'title',
      'description',
      'default_value',
      'required',
      'rows',
      'cols',
      'key',
    ),
    'default'    => array(
      '#title'         => t('New textarea'),
      '#type'          => 'textarea',
      '#default_value' => '',
    ),
  );

  // Allow other modules to modify the fields.
  drupal_alter('config_builder_form_builder_types', $fields);

  return array(
    'config_builder' => $fields
  );
}

/**
 * Implements hook_form_builder_properties().
 *
 * @param $form_type
 *
 * @return array
 */
function config_builder_ui_form_builder_properties($form_type) {
  $properties = array();
  if ('config_builder' == $form_type) {
    $properties['tree'] = array(
      'form' => 'config_builder_ui_property_tree_form',
    );
  }
  drupal_alter('config_builder_form_builder_properties', $properties, $form_type);

  return $properties;
}

/**
 * Configuration form for the "tree" property.
 *
 * @param $form_state
 * @param $form_type
 * @param $element
 *
 * @return array
 */
function config_builder_ui_property_tree_form(&$form_state, $form_type, $element) {
  $form = array();

  $form['tree'] = array(
    '#title'         => t('Tree'),
    '#type'          => 'checkbox',
    '#default_value' => $element['#tree'],
  );

  return $form;
}
