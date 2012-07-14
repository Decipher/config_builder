<?php
/**
 * @file
 * Chaos tool suite module integration.
 */

/**
 * Implements hook_ctools_plugin_directory().
 */
function config_builder_ctools_plugin_directory($module, $plugin) {
  if ($module == 'ctools' && !empty($plugin)) {
    return "plugins/{$plugin}";
  }
}

/**
 * Implements hook_ctools_plugin_api().
 */
function config_builder_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "config_builder" && $api == "config_builder") {
    return array("version" => "1");
  }
}
