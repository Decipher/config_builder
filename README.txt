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
* Integrates with:
  * Drupal Contextual links module:
    - Adds a hover link for quick editing configuration pages.
    - Adds contextual link tokens for quick editing variables.
  * Variable module (requires patch - http://drupal.org/files/variable_form_element_element-1688586-8.patch):
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



Roadmap / Todo
--------------------------------------------------------------------------------

- Configurable Menus.
- Exportable as standalone module.
- Domain integration.
