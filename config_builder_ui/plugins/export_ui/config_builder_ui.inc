<?php

/**
 * @file
 * CTools Export UI plugin for Configuration Builder pages.
 */

/**
 * CTools Export UI required function for plugin definition
 */
function config_builder_ui_config_builder_ui_ctools_export_ui() {
  return array(
    'schema'                => 'config_builder',
    'access'                => 'administer config builder',
    'menu'                  => array(
      'menu prefix'      => 'admin/structure',
      'menu item'        => 'config_builder',
      'menu title'       => 'Configuration builder',
      'menu description' => 'Administer Configuration pages.',
    ),
    'title singular'        => t('configuration page'),
    'title singular proper' => t('Configuration page'),
    'title plural'          => t('configuration pages'),
    'title plural proper'   => t('Configuration pages'),
    'handler'               => 'config_builder_ui',
    'form'                  => array(
      'settings' => 'config_builder_ui_export_ui_form',
      'submit'   => 'config_builder_ui_export_ui_form_submit',
    ),
    'export'                => array(
      'admin_title'       => 'label',
      'admin_description' => 'description',
    ),
  );
}

/**
 * Configuration Builder settings form.
 *
 * @param $form
 * @param $form_state
 */
function config_builder_ui_export_ui_form(&$form, &$form_state) {
  $item = $form_state['item'];

  // Basic information fieldset.
  $form['info']['#title']       = t('Basic information');
  $form['info']['#type']        = 'fieldset';
  $form['info']['#collapsible'] = TRUE;
  $form['info']['#collapsed']   = $form_state['op'] != 'add';

  // Page settings.
  $form['page'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Page settings'),
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
  );

  $form['page']['path'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Path'),
    '#field_prefix'  => $GLOBALS['base_url'] . base_path(),
    '#default_value' => $item->path,
    '#required'      => TRUE,
  );

  // Veritcal tabs.
  $form['page']['settings'] = array(
    '#type' => 'vertical_tabs',
  );

  // Access settings.
  $form['page']['access'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Access'),
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
    '#tree'        => TRUE,
    '#group'       => 'settings',
  );

  $form['page']['access']['type'] = array(
    '#type'          => 'select',
    '#title'         => t('Type'),
    '#options'       => array(
      'user_access'                => t('Permission'),
      'config_builder_role_access' => t('Role'),
    ),
    '#default_value' => isset($item->access['type']) ? $item->access['type'] : NULL,
  );

  // Menu settings.
  $form['page']['menu'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Menu'),
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
    '#tree'        => TRUE,
    '#group'       => 'settings',
  );

  $form['page']['menu']['type'] = array(
    '#type'          => 'radios',
    '#title'         => t('Type'),
    '#options'       => array(
      'none'        => t('No menu entry'),
      'normal'      => t('Normal menu entry'),
      'tab'         => t('Menu tab'),
      'default tab' => t('Default menu tab'),
      'action'      => t('Local action'),
    ),
    '#default_value' => isset($item->menu['type']) ? $item->menu['type'] : 'none',
  );

  $form['page']['menu']['title'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Title'),
    '#default_value' => isset($item->menu['title']) ? $item->menu['title'] : NULL,
    '#description'   => t('If set to normal or tab, enter the text to use for the menu item.'),
    '#size'          => 60,
    '#maxsize'       => 128,
    '#states'        => array(
      'invisible' => array(
        ':input[name="menu[type]"]' => array('value' => 'none'),
      ),
    ),
  );

  $form['page']['menu']['menu'] = array(
    '#type'          => 'select',
    '#title'         => t('Menu'),
    '#options'       => menu_get_menus(),
    '#default_value' => isset($item->menu['menu']) ? $item->menu['menu'] : NULL,
    '#description'   => t('Insert item into an available menu.'),
    '#states'        => array(
      'visible' => array(
        ':input[name="menu[type]"]' => array('value' => 'normal'),
      ),
    ),
  );

  $form['page']['menu']['weight'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Weight'),
    '#default_value' => isset($item->menu['weight']) ? $item->menu['weight'] : 0,
    '#description'   => t('The lower the weight the higher/further left it will appear.'),
    '#size'          => 60,
    '#maxsize'       => 128,
    '#states'        => array(
      'invisible' => array(
        ':input[name="menu[type]"]' => array('value' => 'none'),
      ),
    ),
  );

  $form['page']['menu']['parent'] = array(
    '#type'   => 'container',
    '#states' => array(
      'visible' => array(
        ':input[name="menu[type]"]' => array('value' => 'default tab'),
      ),
    ),
  );

  $form['page']['menu']['parent']['type'] = array(
    '#type'          => 'radios',
    '#title'         => t('Parent menu item'),
    '#options'       => array(
      'none'   => t('No menu entry'),
      'normal' => t('Normal menu item'),
      'tab'    => t('Menu tab'),
    ),
    '#default_value' => isset($item->menu['parent']['type']) ? $item->menu['parent']['type'] : 'none',
    '#description'   => t('When providing a menu item as a default tab, Drupal needs to know what the parent menu item of that tab will be. Sometimes the parent will already exist, but other times you will need to have one created. The path of a parent item will always be the same path with the last part left off. i.e, if the path to this view is <em>foo/bar/baz</em>, the parent path would be <em>foo/bar</em>.'),
    '#states'        => array(
      'visible' => array(
        ':input[name="menu[type]"]' => array('value' => 'default tab'),
      ),
    ),
  );

  $form['page']['menu']['parent']['title'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Parent item title'),
    '#default_value' => isset($item->menu['parent']['title']) ? $item->menu['parent']['title'] : NULL,
    '#description'   => t('If creating a parent menu item, enter the title of the item.'),
    '#size'          => 60,
    '#maxsize'       => 128,
    '#states'        => array(
      'invisible' => array(
        ':input[name="menu[parent][type]"]' => array('value' => 'none'),
      ),
    ),
  );

  $form['page']['menu']['parent']['menu'] = array(
    '#type'          => 'select',
    '#title'         => t('Parent item menu'),
    '#options'       => menu_get_menus(),
    '#default_value' => isset($item->menu['parent']['menu']) ? $item->menu['parent']['menu'] : NULL,
    '#description'   => t('Insert item into an available menu.'),
    '#states'        => array(
      'visible' => array(
        ':input[name="menu[parent][type]"]' => array('value' => 'normal'),
      ),
    ),
  );

  $form['page']['menu']['parent']['weight'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Tab weight'),
    '#default_value' => isset($item->menu['parent']['weight']) ? $item->menu['parent']['weight'] : 0,
    '#description'   => t('If the parent menu item is a tab, enter the weight of the tab. The lower the number, the more to the left it will be.'),
    '#size'          => 5,
    '#maxsize'       => 128,
    '#states'        => array(
      'visible' => array(
        ':input[name="menu[parent][type]"]' => array('value' => 'tab'),
      ),
    ),
  );

  // Get list of permissions.
  $perms       = array();
  $module_info = system_get_info('module');
  foreach (module_implements('permission') as $module) {
    $permissions = module_invoke($module, 'permission');
    foreach ($permissions as $name => $perm) {
      $perms[$module_info[$module]['name']][$name] = strip_tags($perm['title']);
    }
  }
  ksort($perms);

  $form['page']['access']['user_access'] = array(
    '#type'          => 'select',
    '#title'         => t('Permission'),
    '#options'       => $perms,
    '#default_value' => isset($item->access['user_access']) ? $item->access['user_access'] : NULL,
    '#description'   => t('Only users with the selected permission flag will be able to access this configuration page.'),
    '#states'        => array(
      'visible' => array(
        ':input[name="access[type]"]' => array('value' => 'user_access'),
      ),
    ),
  );

  // Get a list of roles.
  $roles  = array();
  $result = db_select('role', 'r')->fields('r')->execute()->fetchAll();
  foreach ($result as $role) {
    $roles[$role->name] = $role->name;
  }

  $form['page']['access']['config_builder_role_access'] = array(
    '#type'          => 'checkboxes',
    '#title'         => t('Role'),
    '#options'       => $roles,
    '#default_value' => isset($item->access['config_builder_role_access']) ? $item->access['config_builder_role_access'] : array(),
    '#description'   => t('Only the checked roles will be able to access this configuration page.'),
    '#states'        => array(
      'visible' => array(
        ':input[name="access[type]"]' => array('value' => 'config_builder_role_access'),
      ),
    ),
  );

  // Form builder.
  $form['form_builder_id'] = array('#type' => 'hidden');
  if (!empty($item->name)) {
    $form['form_builder_id']['#value'] = $item->name;
  }
  else {
    $form['form_builder_id']['#value'] = isset($form_state['input']['form_builder_id']) ? $form_state['input']['form_builder_id'] : drupal_substr(md5(REQUEST_TIME . rand(1000, 9999)), 0, 32);
  }

  module_load_include('inc', 'form_builder', 'includes/form_builder.admin');
  module_load_include('inc', 'form_builder', 'includes/form_builder.api');
  module_load_include('inc', 'form_builder', 'includes/form_builder.cache');

  $form_type = 'config_builder';
  $form_id   = $form['form_builder_id']['#value'];

  // Set the current form type (used for display of the sidebar block).
  form_builder_active_form($form_type, $form_id);

  // Load the current state of the form.
  $form_structure = _config_builder_form_builder_load_form($item, $form_id);

  $form['fapi']                                      = array(
    '#type'        => 'fieldset',
    '#title'       => t('Settings form'),
    '#collapsible' => FALSE,
    '#collapsed'   => FALSE,
  );
  $form['fapi']['form_builder_preview']              = form_builder_preview($form, $form_state, $form_structure, $form_type, $form_id);
  $form['fapi']['form_builder_positions']            = form_builder_positions($form, $form_state, $form_structure, $form_type, $form_id);
  $form['fapi']['form_builder_positions']['#prefix'] = '<div id="form-builder-positions">';
  $form['fapi']['form_builder_positions']['#suffix'] = '</div>';
  unset($form['fapi']['form_builder_positions']['submit']);

  $form['buttons']['edit'] = array(
    '#type'                    => 'submit',
    '#value'                   => t('Save & Edit'),
    '#limit_validation_errors' => _config_builder_ui_limit_validation_errors(),
    '#submit'                  => array('ctools_export_ui_edit_item_form_submit'),
  );
}

/**
 * Helper function; Return array for #limit_validation_errors.
 */
function _config_builder_ui_limit_validation_errors() {
  return array(
    array('access'),
    array('description'),
    array('form_builder_id'),
    array('form_builder_positions'),
    array('label'),
    array('menu'),
    array('name'),
    array('path'),
  );
}

/**
 * Submit callback for Configuration Builder settings form.
 *
 * @param $form
 * @param $form_state
 */
function config_builder_ui_export_ui_form_submit(&$form, &$form_state) {
  module_load_include('inc', 'form_builder', 'includes/form_builder.admin');
  module_load_include('inc', 'form_builder', 'includes/form_builder.api');
  module_load_include('inc', 'form_builder', 'includes/form_builder.cache');

  $form_id    = $form_state['values']['form_builder_id'];
  $form_cache = form_builder_cache_load('config_builder', $form_id);

  $form_state['values']['fapi'] = array();
  if (is_array($form_cache)) {
    if (isset($form_state['values']['form_builder_positions'])) {
      $form_builder_state                                            = array('values' => $form_state['values']['form_builder_positions']);
      $form['fapi']['form_builder_preview']['#form_builder']['form'] = $form_cache;
      form_builder_positions_submit($form['fapi']['form_builder_preview'], $form_builder_state);
    }

    $form_state['item']->fapi     = $form_cache;
    $form_state['values']['fapi'] = $form_state['item']->fapi;
  }

  // Remove the cached form_builder form.
  form_builder_cache_delete('config_builder', $form_id);

  // Rebuild the Configuration builder index.
  form_builder_crud_index_save((object) $form_state['values']);

  // Access settings.
  foreach ($form_state['values']['access'] as $key => &$value) {
    if (is_array($value)) {
      $value = array_filter($value);
    }
    if ('type' != $key && $key != $form_state['values']['access']['type']) {
      unset($form_state['values']['access'][$key]);
    }
  }

  if (t('Save & Edit') == $form_state['values']['op']) {
    $destination         = "admin/structure/config_builder/list/{$form_state['values']['name']}/edit";
    $_GET['destination'] = isset($_GET['destination']) ? "{$destination}?destination={$_GET['destination']}" : $destination;
  }
}

/**
 * Provide a form for displaying an export.
 *
 * @param        $form
 * @param        $form_state
 * @param        $item
 * @param string $title
 *
 * @return mixed
 * @throws Exception
 */
function config_builder_export_ui_export_form($form, &$form_state, $item, $title = '') {
  $form['mode'] = array(
    '#type'          => 'select',
    '#title'         => t('Mode'),
    '#options'       => array(
      'ctools' => t('CTools exportable'),
      'drupal' => t('Drupal API')
    ),
    '#default_value' => 'ctools',
    '#ajax'          => array(
      'callback' => 'config_builder_export_ui_export_form_js',
      'wrapper'  => 'export-wrapper',
    ),
  );

  $form['export'] = array(
    '#type'   => 'container',
    '#prefix' => '<div id="export-wrapper">',
    '#suffix' => '</div>',
  );

  $mode = isset($form_state['values']['mode']) ? $form_state['values']['mode'] : $form['mode']['#default_value'];
  switch ($mode) {
    case 'ctools':
      ctools_include('export');
      $code = ctools_export_crud_export('config_builder', $item);
      break;

    case 'drupal':
      module_load_include('inc', 'config_builder', 'includes/variable');
      $module = isset($form_state['values']['module']) ? $form_state['values']['module'] : t('MYMODULE');

      $form['export']['module'] = array(
        '#type'          => 'textfield',
        '#title'         => t('Module name'),
        '#default_value' => $module,
        '#ajax'          => array(
          'callback' => 'config_builder_export_ui_export_form_js',
          'wrapper'  => 'export-wrapper',
        ),
      );

      $code = theme('config_builder_export', array(
        'item'   => $item,
        'module' => $module
      ));
      break;
  }

  if (isset($code)) {
    $lines = substr_count($code, "\n");

    $form['export']['code'] = array(
      '#type'  => 'textarea',
      '#title' => check_plain($title),
      '#value' => $code,
      '#rows'  => $lines,
    );
  }

  return $form;
}

/**
 * Ajax callback for Configuration builder export page.
 *
 * @param $form
 * @param $form_state
 *
 * @return mixed
 */
function config_builder_export_ui_export_form_js($form, $form_state) {
  return $form['export'];
}
