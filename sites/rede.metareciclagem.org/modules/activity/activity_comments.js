// $Id: activity_comments.js,v 1.1.2.2 2009/03/16 01:01:44 jaydub Exp $

/**
 * Drupal.jsEnabled is a generic wrapper for all Drupal JavaScript.
 */
Drupal.behaviors.activityComments = function(context) {
  $('.activity-comments-click-to-show', context).bind('click', function() {
    $(this).parent().siblings('.activity-comments-form-hidden').slideToggle('fast');
  });
};
