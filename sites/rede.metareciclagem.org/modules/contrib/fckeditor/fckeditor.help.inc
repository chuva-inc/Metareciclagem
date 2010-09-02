<?php
// $Id: fckeditor.help.inc,v 1.1.2.20 2010/03/10 07:43:32 jorrit Exp $
/**
 * FCKeditor - The text editor for Internet - http://www.fckeditor.net
 * Copyright (C) 2003-2008 Frederico Caldeira Knabben
 *
 * == BEGIN LICENSE ==
 *
 * Licensed under the terms of any of the following licenses at your
 * choice:
 *
 *  - GNU General Public License Version 2 or later (the "GPL")
 *    http://www.gnu.org/licenses/gpl.html
 *
 *  - GNU Lesser General Public License Version 2.1 or later (the "LGPL")
 *    http://www.gnu.org/licenses/lgpl.html
 *
 *  - Mozilla Public License Version 1.1 or later (the "MPL")
 *    http://www.mozilla.org/MPL/MPL-1.1.html
 *
 * == END LICENSE ==
 *
 * @file
 * FCKeditor Module for Drupal 6.x
 *
 * This module allows Drupal to replace textarea fields with FCKeditor.
 *
 * This HTML text editor brings to the web many of the powerful functionalities
 * of known desktop editors like Word. It's really  lightweight and doesn't
 * require any kind of installation on the client computer.
 */

function fckeditor_help_delegate($path, $arg) {
  switch ($path) {
    case 'admin/settings/help#description':
      $output = t('Enables the usage of FCKeditor (WYSIWYG editor) instead of plain text fields.');
      break;

    case 'admin/settings/fckeditor/edit/%':
    case 'admin/settings/fckeditor/add':
      $output = '<p>'. t('FCKeditor is highly configurable. The most commonly used features are listed below. If you want to take a look at all available settings, open %fckconfig and then customize %fckeditor_config to your needs. This is also the only way to define new toolbar sets. It is advised to not edit %fckconfigjs because you may overwrite it accidentally when you update the editor.',
        array(
          '%fckconfig' => drupal_get_path('module', 'fckeditor') .'/fckeditor/fckconfig.js',
          '%fckeditor_config' => drupal_get_path('module', 'fckeditor') .'/fckeditor.config.js',
          '%fckconfigjs' => 'fckconfig.js',
        )) .'</p>';
      break;

    case 'admin/settings/fckeditor/editg':
    case 'admin/settings/fckeditor/add':
      $output = '<p>'. t('The Global Profile allows you to define settings that are common for all profiles. Values defined in other profiles will be appended to the global configuration. This way you can avoid repeating some of the settings that are usually the same in each profile.') .'</p>';
      break;

    case 'admin/settings/fckeditor':
      $output = 
        '<p>'. t('The FCKeditor module allows Drupal to replace textarea fields with a rich text or !wysiwyg editor. This editor brings many of the powerful functionalities of known desktop editors like Word to the web. It\'s relatively lightweight and doesn\'t require any kind of installation on the client computer.',
          array(
            '!wysiwyg' => '<acronym title="'. t('What You See Is What You Get') .'">'. t('WYSIWYG') .'</acronym>',
          )) .'</p>'.
        '<p>'. t('More information about the editor is located at the !fckeditorlink. A small user guide is located at !userguidelink.',
          array(
            '!fckeditorlink' => l(t('FCKeditor homepage'), 'http://ckeditor.com'),
            '!userguidelink' => l(t('FCKeditor userguide'), 'http://docs.cksource.com/FCKeditor_2.x/Users_Guide'),
          )) .'</p>'.
        '<p>'. t('Profiles can be defined based on user roles. A FCKeditor profile can define which pages receive this FCKeditor capability, what buttons or themes are enabled for the editor, how the editor is displayed, and a few other editor functions. It is possible also to define the Global Profile that will hold values that will be appended to all other profiles.') .'</p>'.
        '<p>'. t('Lastly, only users with the %accesspermission !permissionlink will be able to use FCKeditor.',
          array(
            '%accesspermission' => t('access fckeditor'),
            '!permissionlink' => l(t('permission'), 'admin/user/permissions')
          )) .'</p>';
      break;

    case 'admin/help#fckeditor':
      $output  = '<p>'. t('The FCKeditor module allows Drupal to replace textarea fields with a rich text or !wysiwyg editor. This editor brings many of the powerful functionalities of known desktop editors like Word to the web. It\'s relatively lightweight and doesn\'t require any kind of installation on the client computer.',
          array(
            '!wysiwyg' => '<acronym title="'. t('What You See Is What You Get') .'">'. t('WYSIWYG') .'</acronym>',
          )) .'</p>';
      $output .= '<p>'. t('More information about the editor is located at the !fckeditorlink. A small user guide is located at !userguidelink.',
          array(
            '!fckeditorlink' => l(t('FCKeditor homepage'), 'http://ckeditor.com'),
            '!userguidelink' => l(t('FCKeditor userguide'), 'http://docs.cksource.com/FCKeditor_2.x/Users_Guide'),
          )) .'</p>';
      $output .= '<h3>'. t('Configuration') .'</h3>';
      $output .= '<ol>';
      $output .= '<li>'. t('Go to the !fckeditorlink and download the latest version of FCKeditor. Then uncompress the contents of the fckeditor directory of the downloaded file to %fckeditordir.',
        array(
          '!fckeditorlink' => l(t('FCKeditor homepage'), 'http://ckeditor.com/download'),
          '%fckeditordir' => base_path() . drupal_get_path('module', 'fckeditor') .'/fckeditor/',
        )) .'</li>';
      $output .= '<li>'. t('Enable the module as usual from Drupal\'s admin pages.') .'</li>';
      $output .= '<li>'. t('Grant permissions for use of FCKeditor in !adminpath. See the @sectionname section how to enable the file browser feature.',
        array(
          '!adminpath' => l(t('Administer') .' > '. t('User management') .' > '. t('Permissions'), 'admin/user/permissions'),
          '@sectionname' => t('How to enable the built-in file browser'),
        )) .'</li>';
      $output .= '<li>'. t('Under !adminpath, adjust the fckeditor profiles. In each profile you can choose which textareas will be replaced by FCKeditor, select default toolbar and configure some more advanced settings.',
        array(
          '!adminpath' => l(t('Administer') .' > '. t('Site configuration') .' > '. t('FCKeditor'), 'admin/settings/fckeditor'),
        )) .'</li>';
      $output .= '<li>'. t('For the Rich Text Editing to work you also need to configure your !filterlink for the users that may access Rich Text Editing. Either grant those users Full HTML access or use the following:',
        array(
          '!filterlink' => l(t('filters'), 'admin/settings/filters'),
        )) .
        '<br /><code>'. htmlspecialchars('<a> <p> <span> <div> <h1> <h2> <h3> <h4> <h5> <h6> <img> <map> <area> <hr> <br /> <ul> <ol> <li> <dl> <dt> <dd> <table> <tr> <td> <em> <b> <u> <i> <strong> <font> <del> <ins> <sub> <sup> <quote> <blockquote> <pre> <address> <code> <cite> <embed> <object> <param> <strike> <caption>') .'</code></li>';
      $output .= '<li>'. t('To have a better control over line breaks, you should disable %settingname in the chosen filter (recommended).',
        array(
          '%settingname' => t('Line break converter'),
        )) .'</li>';
      $output .= '<li>'. t('Modify the fckeditor.config.js file to custom your needs (optional). You may copy the needed configuration lines from the default FCKeditor configuration settings (%fckconfig), the lines in fckeditor.config.js will override most settings.',
        array(
          '%fckconfig' => base_path() . drupal_get_path('module', 'fckeditor') .'/fckeditor/fckconfig.js',
        )) .'</li>';
      $output .= '</ol>';

      $output .= '<a name="fieldinclexcl"></a>';
      $output .= '<h3>'. t('Defining field inclusion/exclusions') .'</h3>';
      $output .= '<p>'. t('In order to specifically display FCKeditor on those text areas on which you need it, the FCKeditor module provides a powerfull method to define fields that should be enhanced with FCKeditor. The first choice you have to make is whether you want to display FCKeditor on all textareas and define a list of exceptions, or if you don\'t want to display FCKeditor unless it is specifically enabled. This choice is made in the %settingname setting.',
        array(
          '%settingname' => t('Use inclusion or exclusion mode'),
        )) .'</p>';
      $output .= '<p>'. t('Next, the list of exceptions has to be defined. This list follows a specific syntax: the path to a field is defined by specifying the content type followed by @ character, specifying the path followed by dot and appending the field name at the end. You may decide to not use the content type. The field %fieldname on page %pathname would thus be addressed as %result. You can use wildcards * and ? anywhere in this line. If you have a dot in your field name and it causes problems, you can escape it with a slash (\).',
        array(
          '%fieldname' => 'edit-log',
          '%pathname' => 'node/add/page',
          '%result' => 'node/add/page.edit-log',
        )) .'</p>';

      $output .= '<strong>'. t('Some examples:') .'</strong>';
      $output .= '<ul>';
      $output .= '<li><code>node/add/page</code>: '. t('matches all fields on %pathname', array('%pathname' => 'node/add/page')) .'</li>';
      $output .= '<li><code>*.edit-log</code>: '. t('matches all fields called %fieldname on any page', array('%fieldname' => 'edit-log')) .'</li>';
      $output .= '<li><code>blog@*.edit-body</code>: '. t('matches all fields called %fieldname on pages related to node type %typename', array('%fieldname' => 'edit-body', '%typename' => 'blog')) .'</li>';
      $output .= '<li><code>forum@*.*</code>: '. t('matches all fields on pages related to node type %nodetype', array('%nodetype' => 'forum')) .'</li>';
      $output .= '<li><code>node/add/*</code>: '. t('matches all fields on pages such as %pathname1, %pathname2, etc.', array('%pathname1' => 'node/add/page', '%pathname2' => 'node/add/story')) .'</li>';
      $output .= '<li><code>node/add/*.edit-log</code>: '. t('matches all %fieldname fields on pages such as %pathname1, %pathname2, etc.', array('%fieldname' => 'edit-log', '%pathname1' => 'node/add/page', '%pathname2' => 'node/add/story')) .'</li>';
      $output .= '<li><code>node/add/*.edit-user-*</code>: '. t('matches fields starting with %fieldname on pages starting with %pathname', array('%fieldname' => 'edit-user-', '%pathname' => 'node/add/')) .'</li>';
      $output .= '</ul>';

      $output .= '<h3>'. t('Troubleshooting') .'</h3>';
      $output .= '<p>';
      $output .= t('Take a look at !listlink when installing FCKeditor.', array('!listlink' => l(t('list of common problems'), 'http://drupal.fckeditor.net/troubleshooting')));
      $output .= ' '. t('If you are looking for more information, have any trouble in configuration or if you found an issue, please visit the !officiallink.', array('!officiallink' => l(t('official project page'), 'http://drupal.org/project/fckeditor')));
      $output .= ' '. t('More information about how to tune up FCKeditor for your theme can be found !herelink.', array('!herelink' => l(t('here'), 'http://drupal.fckeditor.net/tricks')));
      $output .= '</p>';

      $output .= '<h3>'. t('Plugins: Teaser break and Pagebreak') .'</h3>';
      $output .= '<p>'. t('By default, FCKeditor module comes with two plugins that can handle teaser break (&lt;!--break--&gt;) and pagebreak (&lt;!--pagebreak--&gt;). You can enable any (or even both) of them.') .'</p>';
      $output .= '<ol>';
      $output .= '<li>'. t('Open %fckeditor.config.js and uncomment these three lines:', array('%fckeditor.config.js' => base_path() . drupal_get_path('module', 'fckeditor') .'/fckeditor.config.js')) .'<pre>'."\nFCKConfig.PluginsPath = '../../plugins/';\nFCKConfig.Plugins.Add('drupalbreak');\nFCKConfig.Plugins.Add('drupalpagebreak');\n".'</pre></li>';
      $output .= '<li>'. t('The second step is to add buttons to the toolbar (in the same file). The button names are: <code>DrupalBreak</code>, <code>DrupalPageBreak</code>. For example if you have a toolbar with an array of buttons defined as follows: <pre>!buttons1</pre> simply add those two buttons at the end of array (remember about single quotes): <pre>!buttons2</pre>', array('!buttons1' => "['Image','Flash','Table','Rule','SpecialChar']", '!buttons2' => "['Image','Flash','Table','Rule','SpecialChar', 'DrupalBreak', 'DrupalPageBreak']")) .'</li>';
      $output .= '<li>'. t('Note that the &lt;--pagebreak--&gt; tag is not supported by default in Drupal. You should install the !paginglink module to enable the &lt;!--pagebreak--&gt; tag support. Please refer to the Paging module documentation for detailed installation instructions.', array('!paginglink' => l(t('Paging'), 'http://drupal.org/project/paging'))) .'</li>';
      $output .= '</ol>';

      $output .= '<h3>'. t('Uploading images and files') .'</h3>';
      $output .= '<p>'. t('There are three ways for uploading files:') .'</p>';
      $output .= '<ol>';
      $output .= '<li>'. t('By using the built-in file browser.') .'</li>';
      $output .= '<li>'. t('By using a module like !imcelink, !iblink or !webfmlink.',
        array(
          '!imcelink' => l(t('IMCE'), 'http://drupal.org/project/imce'),
          '!iblink' => l(t('Image Browser'), 'http://drupal.org/project/imagebrowser'),
          '!webfmlink' => l(t('Web File Manager'), 'http://drupal.org/project/webfm'),
        )) .'</li>';
      $output .= '<li>'. t('By using the core upload module.') .'</li>';
      $output .= '</ol>';

      // The rest is untranslated for the moment.
      $output .= '<h3>'. t('How to enable the built-in file browser') .'</h3>';
      $output .= '<p>'. t('The editor gives the end user the flexibility to create a custom file browser that can be integrated on it. The included file browser allows users to view the content of a specific directory on the server and add new content to that directory (create folders and upload files).') .'</p>';
      $output .= '<ol>';
      $output .= '<li>';
      $output .= ' '. t('To enable file browsing you need to edit the connector configuration file in your fckeditor module directory, the file should be in %config.', array('%config' => base_path() . drupal_get_path('module', 'fckeditor') .'/fckeditor/editor/filemanager/connectors/php/config.php'));
      $output .= ' '. t('In this file you will need to enable the file browser by adding one line that includes a file with the special authentication function for Drupal (filemanager.config.php).') .'<br />';
      $output .= ' '. t('Add this code:') .'<br />';
      $output .= ' <pre>  require_once \'../../../../../filemanager.config.php\';</pre>';
      $output .= ' '. t('straight below this line:');
      $output .= ' <pre>  $Config[\'UserFilesAbsolutePath\'] = \'\' ;</pre>';
      $output .= ' '. t('The config.php file also holds some other important settings, please take a look at it and adjust it to your needs (optional).');
      $output .= '</li>';
      $output .= '<li>'. t('Locate file named %settingsphp inside your drupal directory and set %cookiedomain variable to the appropriate domain (remember to uncomment that line). If you not do this, FCKeditor will claim that file browser is disabled.', array('%settingsphp' => 'settings.php', '%cookiedomain' => '$cookie_domain')) .'</li>';
      $output .= '<li>'. t('Enabling file uploads is <strong>a security risk</strong>. That\'s why you have to grant a separate !permissionlink to enable the file browser to certain groups (assign the %uploadpermission permission).', array('!permissionlink' => l(t('permission'), 'admin/user/permissions'), '%uploadpermission' => t('allow fckeditor file uploads'))) .'</li>';
      $output .= '<li>'. t('Lastly, adjust the %filebrowsersection for each !profilelink: set %filebrowsertypesetting to %builtinoption', array('!profilelink' => l(t('profile'), 'admin/settings/fckeditor'), '%filebrowsersection' => t('File browser settings'), '%filebrowsertypesetting' => t('File browser type'), '%builtinoption' => t('Built-in file browser'))) .'</li>';
      $output .= '</ol>';

      $output .= '<h3>'. t('Modules: Image Assist') .'</h3>';
      $output .= '<p>'. t('Image Assist version 1 and 2 can be integrated with FCKeditor. It is no longer necessary to copy a Javascript file.') .'</p>';

      break;
  }
  return !empty($output) ? $output : '';
}