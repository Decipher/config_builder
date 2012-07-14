<?php
/**
 * @file
 * Contextual links module integration.
 */

/**
 * Implements hook_config_builder_form_config_builder_page_callback_alter() on
 * behalf of contextual.module.
 */
function contextual_config_builder_form_config_builder_page_callback_alter(&$form, $form_state) {
  $config = $form_state['build_info']['args'][0];
  $form['#contextual_links'] = array('config_builder' => array('admin/structure/config_builder/list', array($config->name, 'edit')));
}

/**
 * Implements hook_config_builder_token_info_alter() on behalf of
 * contextual.module.
 */
function contextual_config_builder_token_info_alter(&$info) {
  $indexes = config_builder_crud_index_load_all();
  if (!empty($indexes)) {
    foreach ($indexes as $index) {
      // Basic token.
      $info['tokens']['site']["config:{$index->id}:contextual"] = array(
        'name' => $index->title,
        'description' => t('Value of the "@name" configuration variable with a Contextual link to the configuration form.', array('@name' => $index->id)),
      );

      // Token with ability to choose source of default value.
      $info['tokens']['site']["config:{$index->id}:contextual:?"] = array(
        'name' => $index->title,
        'description' => t('Value of the "@name" configuration variable with a Contextual link to the provided configuration form.', array('@name' => $index->id)),
      );
    }

    ksort($info['tokens']['site']);
  }
}

/**
 * Implements hook_config_builder_tokens_alter() on behalf of contextual.module.
 */
function contextual_config_builder_tokens_alter(&$replacements, $context) {
  if ('site' == $context['type']) {
    foreach ($context['tokens'] as $name => $original) {
      $token = explode(':', $name);
      if ('config' == $token[0] && isset($token[2]) && $token[2] == 'contextual') {
        if (isset($token[3])) {
          $index = config_builder_crud_index_load($token[1], $token[3]);
        }
        else {
          $index = config_builder_crud_index_load($token[1]);
        }
        if ($index !== FALSE) {
          $config = config_builder_crud_load($index->config);
          if ($config !== FALSE) {
            // Build contextually linked element.
            $element = array(
              'markup' => array(
                '#markup' => $index->default_value,
              ),
              'contextual_links' => array(
                '#type' => 'contextual_links',
                '#contextual_links' => array(
                  'config_builder' => array($config->path, array()),
                ),
                '#element' => array(
                  '#markup' => $index->default_value,
                ),
              ),
              '#prefix' => '<span class="contextual-links-region">',
              '#suffix' => '</span>',
            );
            $replacements[$original] = render($element);
          }
        }
      }
    }
  }
}

/**
 * Implements hook_menu_contextual_links_alter().
 */
function config_builder_menu_contextual_links_alter(&$links, $router_item, $root_path) {
  // Show configuration page.
  if ('drupal_get_form' == $router_item['page_callback'] && 'config_builder_page_callback' == $router_item['page_arguments'][0]) {
    $links['config_builder-view'] = array_merge(
      $router_item,
      array(
        'title' => 'Edit value',
      )
    );
  }

  // Edit configuration page.
  if ('admin/structure/config_builder/list/%/edit' == $root_path) {
    $links['config_builder-edit'] = array_merge(
      $router_item,
      array(
        'title' => 'Edit configuration page',
      )
    );
  }
}
