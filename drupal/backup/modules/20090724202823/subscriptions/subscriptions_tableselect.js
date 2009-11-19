// $Id: subscriptions_tableselect.js,v 1.1.2.1 2008/01/18 21:47:25 chx Exp $

Drupal.subscriptions_rowToggle = function(ckb) {
  var thisRow = $(ckb).parents('tr:first');
  var controls = $('input, select', thisRow);
  for (var i = 1; i < controls.length; i++) {
    controls[i].style['visibility'] = (ckb.checked ? 'visible' : 'hidden');
  }
}

Drupal.subscriptions_tableSelect = function() {
  // Dynamically hide/show the other columns depending on the checkbox state in the first column.  
  var rows = $('tr', this);
  for (var i = 1; i < rows.length; i++) {
    var row = rows[i];
    var input = $('td:first input:checkbox', row);
    input.click(function(e) {
      Drupal.subscriptions_rowToggle(this);
    });

    Drupal.subscriptions_rowToggle(input[0]);
  }
}

// Global Killswitch
if (Drupal.jsEnabled) {
  $(document).ready(function() {
    $('form table[th.subscriptions-table]').each(Drupal.subscriptions_tableSelect);
  });
}
