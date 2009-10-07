// $Id: layout.js,v 1.2.4.1 2009/04/30 20:09:58 merlinofchaos Exp $
/**
 * @file layout.js 
 *
 * Contains javascript to make layout modification a little nicer.
 */

Drupal.Panels.Layout = {};
Drupal.Panels.Layout.autoAttach = function() {
  $('div.form-item div.layout-icon').click(function() {
    $widget = $('input', $(this).parent());
    // Toggle if a checkbox, turn on if a radio.
    $widget.attr('checked', !$widget.attr('checked') || $widget.is('input[type=radio]'));
  });
};

$(Drupal.Panels.Layout.autoAttach);
