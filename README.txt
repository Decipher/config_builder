The Configuration builder module provides a Form Builder based, drag and drop
interface for building custom, exportable, configuration pages.

This can be used to create a unified settings form bringing important settings
(Site name, Google analytics account, etc) into one easy to manage page, or for
creating custom settings forms as needed.

Configuration builder was written by Stuart Clark and is maintained by Stuart
Clark (deciphered) and Brian Gilbert (realityloop) of Realityloop Pty Ltd.
- http://www.realityloop.com
- http://twitter.com/realityloop



Features
--------------------------------------------------------------------------------

* Drag and Drop form builder interface.
* Exportable via CTools and Features module.
* Configuration variables provided as tokens.
* Set page access by:
  * User permission.
  * User role(s).
* Provides a block per configuration page.
* Exportable as:
  * Drupal API hooks via:
    * Configuration builder export interface.
  * CTools exportable via:
    * Configuration builder export interface.
    * CTools Bulk Export module.
    * Features module.
* Integrates with:
  * Drupal Contextual links module:
    - Adds a hover link for quick editing configuration pages.
    - Adds contextual link tokens for quick editing variables.
  * Variable module:
    - Adds Variable element for Form Builder for any declared variables.
    - Declares all created variables with hook_variable_info().



Required Modules
--------------------------------------------------------------------------------

* Chaos tool suite - http://drupal.org/project/ctools
* Form Builder - http://drupal.org/project/form_builder



Recommended Modules
--------------------------------------------------------------------------------

* Features - http://drupal.org/project/features
* Variable - http://drupal.org/project/variable



Makefile entries
--------------------------------------------------------------------------------

For easy downloading of Configuration Builder and it's required/recommended
modules and/or libraries, you can use the following entries in your makefile:


  projects[ctools][subdir] = contrib
  projects[ctools][version] = 1.4

  projects[form_builder][subdir] = contrib
  projects[form_builder][version] = 1.4

  projects[options_element][subdir] = contrib
  projects[options_element][version] = 1.10

  projects[variable][subdir] = contrib
  projects[variable][version] = 2.4



Roadmap / Todo
--------------------------------------------------------------------------------

- Configurable Menus.
- Domain integration.
