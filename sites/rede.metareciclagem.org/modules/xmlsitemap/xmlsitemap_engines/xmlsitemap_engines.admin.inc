<?php
// $Id: xmlsitemap_engines.admin.inc,v 1.1.2.17 2009/08/25 16:52:52 earnie Exp $


/**
 * @file
 * XML sitemap engines settings UI.
 */

/**
 * @addtogroup xmlsitemap
 * @{
 */

/*****************************************************************************
 * Menu callbacks / form builders, submit/validate functions.
 ****************************************************************************/

/**
 * Form builder; return the search engine settings form.
 */
function xmlsitemap_engines_settings() {
  $form['submission'] = array(
    '#type' => 'fieldset',
    '#title' => t('Submission settings'),
    '#collapsible' => TRUE,
  );
  $form['submission']['xmlsitemap_engines_submit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Submit the sitemap when content changes'),
    '#description' => t('If enabled, the search engines will be notified of changes to the sitemap each time the sitemap content is changed.'),
    '#default_value' => variable_get('xmlsitemap_engines_submit', FALSE),
  );
  $form['submission']['xmlsitemap_engines_cron_submit_frequency'] = array(
    '#type' => 'select',
    '#title' => t('Frequency of sitemap submission'),
    '#description' => t('The rate at which the sitemap is submitted to the search engines.'),
    '#default_value' => variable_get('xmlsitemap_engines_cron_submit_frequency', 3600),
    '#options' => array(
      '29030400' => t('Yearly'),
      '14515200' => t('Every 6 months'),
      '2419200' => t('Monthly'),
      '1296000' => t('Every 15 days'),
      '604800' => t('Weekly'),
      '86400' => t('Daily'),
      '3600' => t('Hourly'),
      '-1' => t('Never'),
    ),
  );
  // Ask.com fields.
  $form['ask'] = array(
    '#type' => 'fieldset',
    '#title' => t('Ask.com'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['ask']['xmlsitemap_engines_ask_submit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Submit the sitemap to Ask.com'),
    '#default_value' => variable_get('xmlsitemap_engines_ask_submit', FALSE),
  );
  $form['ask']['xmlsitemap_engines_ask_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Submission URL'),
    '#description' => t('The URL to submit the sitemap to. Use %placeholder as placeholder for the sitemap URL.', array('%placeholder' => '[sitemap]')),
    '#value' => variable_get('xmlsitemap_engines_ask_url', 'http://submissions.ask.com/ping?sitemap=[sitemap]'),
    '#disabled' => TRUE,
  );
  // Google fields.
  $form['google'] = array(
    '#type' => 'fieldset',
    '#title' => t('Google'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['google']['xmlsitemap_engines_google_submit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Submit the sitemap to Google'),
    '#default_value' => variable_get('xmlsitemap_engines_google_submit', FALSE),
  );
  $form['google']['xmlsitemap_engines_google_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Submission URL'),
    '#description' => t('The URL to submit the sitemap to. Use %placeholder like placeholder for the sitemap URL.', array('%placeholder' => '[sitemap]')),
    '#value' => variable_get('xmlsitemap_engines_google_url', 'http://www.google.com/webmasters/tools/ping?sitemap=[sitemap]'),
    '#disabled' => TRUE,
  );
  $form['google']['xmlsitemap_engines_google_verify'] = array(
    '#type' => 'textfield',
    '#title' => t('Verification link'),
    '#description' => t('In order to show statistics, Google will ask you to verify that you control this site by creating a file with a certain name. Enter that name here and the XML sitemap module will create a path to that file name. This will only work if you have clean URLs enabled.'),
    '#default_value' => variable_get('xmlsitemap_engines_google_verify', ''),
  );
  // Moreover.com fields.
  $form['moreover'] = array(
    '#type' => 'fieldset',
    '#title' => t('Moreover.com'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['moreover']['xmlsitemap_engines_moreover_submit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Submit the sitemap to Moreover.com'),
    '#default_value' => variable_get('xmlsitemap_engines_moreover_submit', FALSE),
  );
  $form['moreover']['xmlsitemap_engines_moreover_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Submission URL'),
    '#description' => t('The URL to submit the sitemap to. Use %placeholder like placeholder for the sitemap URL.', array('%placeholder' => '[sitemap]')),
    '#value' => variable_get('xmlsitemap_engines_moreover_url', 'http://api.moreover.com/ping?u=[sitemap]'),
    '#disabled' => TRUE,
  );
  // Bing fields.
  $form['bing'] = array(
    '#type' => 'fieldset',
    '#title' => t('Bing (formerly Live Search)'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['bing']['xmlsitemap_engines_bing_submit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Submit the sitemap to Bing'),
    '#default_value' => variable_get('xmlsitemap_engines_bing_submit', FALSE),
  );
  $form['bing']['xmlsitemap_engines_bing_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Submission URL'),
    '#description' => t('The URL to submit the sitemap to. Use %placeholder like placeholder for the sitemap URL.', array('%placeholder' => '[sitemap]')),
    '#value' => variable_get('xmlsitemap_engines_bing_url', 'http://www.bing.com/webmaster/ping.aspx?siteMap=[sitemap]'),
    '#disabled' => TRUE,
  );
  $form['bing']['xmlsitemap_engines_bing_verify'] = array(
    '#type' => 'textfield',
    '#title' => t('Authentication file'),
    '#description' => t('Before allowing you to view additional information, Bing will ask you to verify that you control this site by creating a file with a certain name. Enter that name here, and XML sitemap will create a path to that file name. This will only work if you have clean URLs enabled.'),
    '#default_value' => variable_get('xmlsitemap_engines_bing_verify', ''),
  );
  $form['bing']['xmlsitemap_engines_bing_verify_string'] = array(
    '#type' => 'textfield',
    '#title' => t('Bing authentication tag'),
    '#description' => t('Bing will give you an authentication tag.'),
    '#default_value' => variable_get('xmlsitemap_engines_bing_verify_string', ''),
  );
  // Yahoo! fields.
  $form['yahoo'] = array(
    '#type' => 'fieldset',
    '#title' => t('Yahoo!'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['yahoo']['xmlsitemap_engines_yahoo_submit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Submit the sitemap to Yahoo!'),
    '#default_value' => variable_get('xmlsitemap_engines_yahoo_submit', FALSE),
  );
  $form['yahoo']['xmlsitemap_engines_yahoo_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Submission URL'),
    '#description' => t('The URL to submit the sitemap to. Use %placeholder like placeholder for the sitemap URL.', array('%placeholder' => '[sitemap]')),
    '#value' => variable_get('xmlsitemap_engines_yahoo_url', 'http://search.yahooapis.com/SiteExplorerService/V1/ping?sitemap=[sitemap]'),
    '#disabled' => TRUE,
  );
  $form['yahoo']['xmlsitemap_engines_yahoo_verify'] = array(
    '#type' => 'textfield',
    '#title' => t('Verification link'),
    '#description' => t('Before allowing you to view additional information, Yahoo! will ask you to verify that you control this site by creating a file with a certain name. Enter that name here, and XML sitemap will create a path to that file name. This will only work if you have clean URLs enabled.'),
    '#default_value' => variable_get('xmlsitemap_engines_yahoo_verify', ''),
  );
  $form['yahoo']['xmlsitemap_engines_yahoo_verify_string'] = array(
    '#type' => 'textfield',
    '#title' => t('Authentication key'),
    '#description' => t('Yahoo! will ask you to put an authentication key in the verification file.'),
    '#default_value' => variable_get('xmlsitemap_engines_yahoo_verify_string', ''),
  );
  $form = system_settings_form($form);
  $form['#submit'][] = 'xmlsitemap_engines_settings_submit';
  return $form;
}

/**
 * Submit the settings form.
 */
function xmlsitemap_engines_settings_submit($form, &$form_state) {
  variable_set('menu_rebuild_needed', TRUE);
}

/**
 * @} End of "addtogroup xmlsitemap".
 */

