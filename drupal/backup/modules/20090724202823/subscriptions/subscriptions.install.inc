<?php
// $Id: subscriptions.install.inc,v 1.1.2.2 2008/07/27 15:37:01 salvis Exp $

/**
 * User information message at installation and pre-2.0 upgrade time.
 */
function _subscriptions_install_information() {
  $t = get_t();
  $tr = $t;
  drupal_set_message($t('Note: for standard Subscriptions functionality you need to enable the following modules:')
                     .'<ul><li>'. $tr('Subscriptions UI')
                     .'</li><li>'. $tr('Subscriptions Mail ')
                       .'<ul><li>'. $t('!mail_edit (required)', array('!mail_edit' => l($tr('Mail Editor'), 'http://drupal.org/project/mail_edit', array('target' => '_blank')))) .'</li>'
                       .'<li>'. $t('!HTML_to_text (strongly recommended)', array('!HTML_to_text' => l($tr('HTML to text'), 'http://drupal.org/project/html_to_text', array('target' => '_blank')))) .'</li></ul>'
                     .'</li><li>'. $tr('Content Subscriptions')
                     .'</li><li>'. $tr('Taxonomy Subscriptions')
                     .'</li></ul>');
                     
}

