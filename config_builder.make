core = 7.x
api = 2

projects[ctools][subdir] = 'contrib'
projects[ctools][version] = '1.0'

projects[form_builder][subdir] = 'contrib'
projects[form_builder][version] = '1.0'

projects[options_element][subdir] = 'contrib'
projects[options_element][version] = '1.7'

projects[variable][subdir] = 'contrib'
projects[variable][version] = '2.1'
; Add 'variable_form_element' element - http://drupal.org/node/1688586#comment-6246450
projects[variable][patch][] = 'http://drupal.org/files/variable_form_element_element-1688586-8.patch'
