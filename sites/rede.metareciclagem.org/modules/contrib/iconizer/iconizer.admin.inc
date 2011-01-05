<?php
// $Id: iconizer.admin.inc,v 1.1.2.3 2010/11/26 13:39:26 thepanz Exp $

/**
 * @file
 * Admin settings for Iconizer Module
 */

/**
 * Admin hook
 */
function iconizer_admin_form() {
  $form = array();
  drupal_add_js(drupal_get_path('module', 'iconizer') . '/iconizer.admin.js');

  /**
  if(!defined('ICONIZER_NO_THEMES')) {
    if (variable_get('iconizer_themes_enable', 0) !== 0 &&
        !file_check_directory(file_create_path(variable_get('iconizer_themes_path', 'iconizer_themes')), FILE_CREATE_DIRECTORY)) {
      $error = theme('error', t('The themes directory does not exist, or is not writable.'));
    }
    $form['themes'] = array(
      '#type' => 'fieldset',
      '#title' => t('Icon themes settings'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE
    );
    $form['themes']['iconizer_themes_enable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable icons themes'),
      '#default_value' => variable_get('iconizer_themes_enable', 0),
      '#description' => t('Enable this feature to access and choose icons themes for \'Admin\', \'Files\' and \'Protocols\'')
    );  
    $form['themes']['iconizer_themes_path'] = array(
      '#type' => 'textfield',
      '#title' => t('Themes path'),
      '#default_value' => variable_get('iconizer_themes_path', ''),
      '#size' => 45,
      '#maxlength' => 255,
      '#description' => t('Subdirectory in the directory "%dir" where iconizer themes be stored.', array('%dir' => variable_get('file_directory_path', 'files') . '/')) . $error,
    );
  }
  */
  
  // Creating Fieldsets
  // Admin-section
  $form['admin_icons'] = array(
    '#type' => 'fieldset',
    '#title' => t('Admin icons'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['admin_icons']['iconizer_admin_icons'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable icons in Admin pages'),
    '#default_value' => variable_get('iconizer_admin_icons', 1),
  );
  
  // Files icons
  $form['files_icons'] = array(
    '#type' => 'fieldset',
    '#title' => t('Files link icons'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['files_icons']['iconizer_files_icons'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable icons for files links'),
    '#default_value' => variable_get('iconizer_files_icons', 0),
  );
  /*
   $access = user_access('use PHP for block visibility');
   if ($access) {
      $options[] = t('Show if the following PHP code returns <code>TRUE</code> (PHP-mode, experts only).');
      $description .= ' '. t('If the PHP-mode is chosen, enter PHP code between %php. Note that executing incorrect PHP-code can break your Drupal site.', array('%php' => '<?php ?>'));
    }
  */
  
  $options = array(
    0 => t('Show on every page except the listed pages.'),
    1 => t('Show on only the listed pages.')
  );
  $description = t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>'));
  
  $form['files_icons']['iconizer_file_icons_visibility'] = array(
    '#type' => 'radios',
    '#title' => t('Show File icons on specific pages'),
    '#options' => $options,
    '#default_value' => variable_get('iconizer_file_icons_visibility', 0),
    '#prefix' => '<div class="iconizer_file_icons_visibility">',
    '#suffix' => '<div>',
  );
  $form['files_icons']['iconizer_file_icons_visibility_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Pages'),
    '#default_value' => variable_get('iconizer_file_icons_visibility_pages', ''),
    '#description' => $description,
  );
  
  // Protocols icons
  $form['proto_icons'] = array(
    '#type' => 'fieldset',
    '#title' => t('Protocols link icons'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );

  $form['proto_icons']['iconizer_proto_icons'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable icons for protocols links'),
    '#default_value' => variable_get('iconizer_proto_icons', 0),
  );
  
  /*
  if(user_access('choose iconizer themes')) {
    if(variable_get('iconizer_themes_enable', 0) !== 0) {
      $form['admin_icons']['iconizer_admin_icons_theme'] = array(
       '#type' => 'select',
        '#title' => t('Choose Admin icons theme'),
        '#default_value' => variable_get('iconizer_admin_icons_theme','default'),
        '#options' => _iconizer_get_themes('admin'),
        '#description' => t('Theme for Admin links icons.'),
      );
      $form['files_icons']['iconizer_files_icons_theme'] = array(
       '#type' => 'select',
        '#title' => t('Choose Files icons theme'),
        '#default_value' => variable_get('iconizer_files_icons_theme','default'),
        '#options' => _iconizer_get_themes('files'),
        '#description' => t('Theme for Files links icons.'),
      );
      $form['proto_icons']['iconizer_proto_icons_theme'] = array(
       '#type' => 'select',
        '#title' => t('Choose Protocols icons theme'),
        '#default_value' => variable_get('iconizer_proto_icons_theme','default'),
        '#options' => _iconizer_get_themes('files'),
        '#description' => t('Theme for Protocols links icons.'),
      );
    }
    else {
      $error = theme('error', t('The themes have been disabled.'));
      //$form = array();
    }
  }
  */
  
  // Per-page links visibility
  $options = array(t('Show on every page except the listed pages.'), t('Show on only the listed pages.'));
  $description = t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>'));  
  
  return system_settings_form($form);
}