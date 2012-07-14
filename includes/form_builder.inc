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

      _config_builder_form_builder_prepare_element_recurse($form);
      form_builder_cache_save('config_builder', $form_id, $form);
    }
  }

  return $form;
}

/**
 * Recursively prepare form builder element.
 */
function _config_builder_form_builder_prepare_element_recurse(&$form) {
  foreach (element_children($form) as $key) {
    $form[$key]['#key'] = $key;
    $form[$key]['#form_builder'] = array(
      'element_id' => $key,
      'element_type' => $form[$key]['#type'],
      'configurable' => TRUE,
      'removable' => TRUE,
    );
    _config_builder_form_builder_prepare_element_recurse($form[$key]);
  }
}

/**
 * Recursive function for pretty-printing of FAPI arrays.
 */
function _config_builder_form_builder_export_recurse($form, $parents = array()) {
  $output = '';

  // Sort this level of the array according to weight.
  uasort($form, 'element_sort');

  // Print out this parent element and it's properties.
  $properties = element_properties($form);
  $omit = array('#form_builder', '#key');
  if (count($properties)) {
    $output .= _config_builder_form_builder_export_variable_name($parents) . " = array(\n";
    foreach (element_properties($form) as $property) {
      if (!in_array($property, $omit)) {
        if (is_array($form[$property])) {
          $output .= "  '". $property . "' => array(\n";
          foreach ($form[$property] as $key => $value) {
            if ($property == '#options') {
              $output .= "    '" . $key . "' => t('". $value ."'),\n";
            }
            else {
              $output .= "    '" . $key . "' => '". $value ."',\n";
            }
          }
          $output .= "  ),\n";
        }
        else {
          if (($property == '#title') || ($property == '#description')) {
            $output .= "  '". $property . "' => t('" . str_replace("'", "\'", $form[$property]) ."'),\n";
          }
          else {
            $output .= "  '". $property . "' => '" . $form[$property] ."',\n";
          }
        }
      }
    }
    $output .= ");\n";
  }
  else {
    $output .= _config_builder_form_builder_export_variable_name($parents) . " = array();\n";
  }

  foreach (element_children($form) as $key) {
    $parents[] = $key;
    $output .= _config_builder_form_builder_export_recurse($form[$key], $parents);
    array_pop($parents);
  }

  return $output;
}

function _config_builder_form_builder_export_variable_name($parents) {
  $output = '$form';
  foreach ($parents as $parent) {
    $output .= "['". $parent ."']";
  }
  return $output;
}

/**
 * Implements hook_form_builder_types().
 */
function config_builder_form_builder_types() {
  $fields = array();

  $fields['fieldset'] = array(
    'title' => t('Fieldset'),
    'properties' => array(
      'title',
      'description',
      'collapsible',
      'collapsed',
      'key',
    ),
    'default' => array(
      '#title' => t('New fieldset'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    ),
  );

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
