<?php
// $Id: subscriptions_mail.templates.inc,v 1.1.2.3 2008/03/21 21:34:03 chx Exp $

/**
 * @file
 * Subscriptions module mail templates constants.
 */

define('SUBSCRIPTIONS_COMMENT_MAILKEY', 'subscriptions-comment');
define('SUBSCRIPTIONS_DIGEST_MAILKEY', 'subscriptions-digest');

function subscriptions_mail_template_raw($key) {
  switch ($key) {
  
    case 'SEP':      return // SUBSCRIPTIONS_DEFAULT_SEPARATOR
t('| --------------------------------------------------------------------
');

    case 'SUBJ':     return // SUBSCRIPTIONS_DEFAULT_SUBJECT
t('[!site] !subs_type subscription for !name: !title');

    case 'FOOT':     return // SUBSCRIPTIONS_DEFAULT_FOOTER
t('| This is an automated message. Please do NOT reply to the sender address!
| To manage your subscriptions go to
| !manage_url
');

    case 'BODY':     return // SUBSCRIPTIONS_DEFAULT_BODY
t('| Greetings, !name.
|
| Your subscription on !site
| notifies you of {{!is_new==0?:a new post:
}}{{!is_updated==0?:an updated post:
}}{{!is_old==0?:new comments:
}}|
{{!is_published==1?:| ***** This post is unpublished! *****
}}{{!term_name==!term_name?:| Category: !term_name
}}{{!sender_name==!sender_name?:| Author: !sender_name
}}{{!sender_has_contact_page==0?:| Contact: !sender_contact_page
}}| Title: !title
{{!is_old==1?:
!teaser

}}| Link: !url
| Direct unsubscribe link (!subs_type):
| !unsubscribe_url
{{!has_new_comments==1?!SEPARATOR!comments:}}!SEPARATOR!FOOTER', array('!SEPARATOR' => subscriptions_mail_template_raw('SEP'), '!FOOTER' => subscriptions_mail_template_raw('FOOT')));

    case 'CITEM':    return // SUBSCRIPTIONS_DEFAULT_COMMENT_ITEM
t('| {{!comment_is_new==1?New:Updated}} {{!comment_is_published==1?:UNPUBLISHED }}comment:
| Author: !comment_name
| Title: !comment_title

!comment_text

| Link: !comment_url
');

    case 'DSUBJ':    return // SUBSCRIPTIONS_DEFAULT_DIGEST_SUBJECT
t('[!site] Subscription Digest for !name');

    case 'DBODY':    return // SUBSCRIPTIONS_DEFAULT_DIGEST_BODY
t('| Greetings, !name.
|
| Your subscriptions on !site
| notify you of the following changes since the previous digest:
|
!bodies!SEPARATOR!FOOTER', array('!SEPARATOR' => subscriptions_mail_template_raw('SEP'), '!FOOTER' => subscriptions_mail_template_raw('FOOT')));

    case 'DITEM':    return // SUBSCRIPTIONS_DEFAULT_DIGEST_ITEM_BODY
t('{{!sender_name==!sender_name?:| Author: !sender_name
}}| Title: !title
{{!is_new==0?:!teaser
}}| Link: !url
| Direct unsubscribe link (!subs_type):
| !unsubscribe_url
{{!has_new_comments!=1?:!comments}}');

    case 'DITEMCMT': return // SUBSCRIPTIONS_DEFAULT_DIGEST_ITEM_BODY_COMMENT
t('| Comment: !comment_title
');

  }
}

function subscriptions_mail_template($key) {
  global $locale;
  static $templates;
  if (!isset($templates[$locale][$key])) {
    $templates[$locale][$key] = subscriptions_mail_template_raw($key);
  }
  return $templates[$locale][$key];
}


