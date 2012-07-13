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
