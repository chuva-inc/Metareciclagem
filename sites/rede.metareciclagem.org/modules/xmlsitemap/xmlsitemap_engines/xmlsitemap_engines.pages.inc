<?php
// $Id: xmlsitemap_engines.pages.inc,v 1.1.2.3 2009/06/16 13:46:19 earnie Exp $

/**
 * @file
 * XML sitemap engines page callbacks.
 */

/**
 * @addtogroup xmlsitemap
 * @{
 */

/*****************************************************************************
 * Menu callbacks / form builders, submit/validate functions.
 ****************************************************************************/

/**
 * Menu callback; display the verification page.
 */
function xmlsitemap_engines_verify($engine) {
  switch ($engine) {
    case 'google':
      print '<html>'."\n";
      print '  <head>'."\n";
      print '    <title>Hello, Google!</title>'."\n";
      print '  </head>'."\n";
      print '  <body>'."\n";
      print '    <p>Hello, Google!</p>'."\n";
      print '  </body>'."\n";
      print '</html>'."\n";
      break;
    case 'yahoo':
      print variable_get('xmlsitemap_engines_yahoo_verify_string', '');
      break;
    case 'bing':
      print '<?xml version="1.0"?>'."\n";
      print "<users>\n";
      print '    <user>'. variable_get('xmlsitemap_engines_bing_verify_string', '') ."</user>\n";
      print "</users>\n";
      break;
  }
  drupal_page_footer();
  exit;
}


/**
 * @} End of "addtogroup xmlsitemap".
 */
