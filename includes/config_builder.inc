<?php
/**
 * Configuration builder module integration.
 */

/**
 * Implements hook_config_builder_defaults().
 */
function config_builder_config_builder_defaults() {
  $export = array();

  $config_builder = new stdClass();
  $config_builder->disabled = TRUE;
  $config_builder->api_version = 1;
  $config_builder->name = 'site_information';
  $config_builder->label = 'Site information';
  $config_builder->description = 'Replacement form for the system \'Site information\' form.';
  $config_builder->path = 'admin/config/system/site-information';
  $config_builder->access = array(
    'type' => 'user_access',
    'user_access' => 'administer site configuration',
  );
  $config_builder->fapi = '$form = array();
$form[\'site_information\'] = array(
  \'#weight\' => \'0\',
  \'#collapsed\' => \'0\',
  \'#collapsible\' => \'0\',
  \'#title\' => t(\'Site details\'),
  \'#type\' => \'fieldset\',
);
$form[\'site_information\'][\'site_name\'] = array(
  \'#required\' => \'1\',
  \'#title\' => t(\'Site name\'),
  \'#type\' => \'textfield\',
  \'#weight\' => \'0\',
);
$form[\'site_information\'][\'site_slogan\'] = array(
  \'#required\' => \'0\',
  \'#type\' => \'textfield\',
  \'#title\' => t(\'Slogan\'),
  \'#description\' => t(\'How this is used depends on your site\\\'s theme.\'),
  \'#weight\' => \'1\',
);
$form[\'site_information\'][\'site_mail\'] = array(
  \'#required\' => \'1\',
  \'#type\' => \'textfield\',
  \'#title\' => t(\'E-mail address\'),
  \'#description\' => t(\'The <em>From</em> address in automated e-mails sent during registration and new password requests, and other notifications. (Use an address ending in your site\\\'s domain to help prevent this e-mail being flagged as spam.)\'),
  \'#weight\' => \'2\',
);
$form[\'front_page\'] = array(
  \'#weight\' => \'2\',
  \'#collapsed\' => \'0\',
  \'#type\' => \'fieldset\',
  \'#collapsible\' => \'0\',
  \'#title\' => t(\'Front page\'),
);
$form[\'front_page\'][\'default_nodes_main\'] = array(
  \'#multiple_toggle\' => \'1\',
  \'#title\' => t(\'Number of posts on front page \'),
  \'#type\' => \'select\',
  \'#options\' => array(
    \'1\' => t(\'1\'),
    \'2\' => t(\'2\'),
    \'3\' => t(\'3\'),
    \'4\' => t(\'4\'),
    \'5\' => t(\'5\'),
    \'6\' => t(\'6\'),
    \'7\' => t(\'7\'),
    \'8\' => t(\'8\'),
    \'9\' => t(\'9\'),
    \'10\' => t(\'10\'),
    \'11\' => t(\'15\'),
    \'12\' => t(\'20\'),
    \'13\' => t(\'25\'),
    \'14\' => t(\'30\'),
  ),
  \'#multiple\' => \'0\',
  \'#description\' => t(\'The maximum number of posts displayed on overview pages such as the front page.\'),
  \'#key_type_toggled\' => \'0\',
  \'#weight\' => \'0\',
  \'#required\' => \'0\',
);
$form[\'front_page\'][\'site_frontpage\'] = array(
  \'#description\' => t(\'Optionally, specify a relative URL to display as the front page.  Leave blank to display the default content feed.\'),
  \'#type\' => \'textfield\',
  \'#title\' => t(\'Default front page\'),
  \'#weight\' => \'1\',
  \'#size\' => \'40\',
  \'#required\' => \'0\',
  \'#field_prefix\' => \'' . url('', array('absolute' => TRUE)) . '\',
);
$form[\'error_page\'] = array(
  \'#weight\' => \'3\',
  \'#collapsed\' => \'0\',
  \'#type\' => \'fieldset\',
  \'#collapsible\' => \'0\',
  \'#title\' => t(\'Error pages\'),
);
$form[\'error_page\'][\'site_403\'] = array(
  \'#title\' => t(\'Default 403 (access denied) page\'),
  \'#description\' => t(\'This page is displayed when the requested document is denied to the current user. Leave blank to display a generic "access denied" page.\'),
  \'#weight\' => \'0\',
  \'#size\' => \'40\',
  \'#type\' => \'textfield\',
  \'#required\' => \'0\',
  \'#field_prefix\' => \'' . url('', array('absolute' => TRUE)) . '\',
);
$form[\'error_page\'][\'site_404\'] = array(
  \'#title\' => t(\'Default 404 (not found) page\'),
  \'#description\' => t(\'This page is displayed when no other content matches the requested document. Leave blank to display a generic "page not found" page.\'),
  \'#weight\' => \'1\',
  \'#size\' => \'40\',
  \'#type\' => \'textfield\',
  \'#required\' => \'0\',
  \'#field_prefix\' => \'' . url('', array('absolute' => TRUE)) . '\',
);
';
  $export['site_information'] = $config_builder;

  return $export;
}
