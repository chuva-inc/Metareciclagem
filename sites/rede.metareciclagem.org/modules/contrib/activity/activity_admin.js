if (Drupal.jsEnabled) {

  $(document).ready(function() {

    var tokenCount = $('input[name*="token_types"]').size();
    
    if ($('input[name*="token_types"]').filter(':checked').size() == 0) {
      $('input[name*="op_types"]').attr('disabled', true);
      $(":text").parent().hide();
      if (tokenCount > 1) {
        $(":text").parent().parent('fieldset').hide();
      }
    }
    else {
      $('input[name*="token_types"]').not(':checked').each(function() {
        $("input[name*='_" + this.value + "_']").parent().hide();
        if (tokenCount > 1) {
          $("input[name*='_" + this.value + "_']").parent().parent('fieldset').hide();
        }
      });

      $('input[name*="op_types"]').not(':checked').each(function() {
        $("input[name*='_" + this.value + "_']").parent().hide();
      });
    }

    $('input[name*="op_types"]').click(function() {
      operation = this;
      $("input[name*='_" + operation.value + "_']").each(function() {
        var fieldset = $(this).parents('fieldset:first');
        if ($(fieldset).is('.collapsed')) {
          Drupal.toggleFieldset(fieldset);
        }
        if ($(operation).is(':checked')) {
          $(this).parent().show();
        }
        else {
          $(this).parent().fadeOut('normal');
        }
      });
    });

    $('input[name*="token_types"]').click(function() {
      token = this;
      if ($('input[name*="token_types"]').filter(':checked').size() == 0) {
        $('input[name*="op_types"]').attr('disabled', true);
      }
      else {
        $('input[name*="op_types"]').attr('disabled', false);
      }

      $("input[name*='_" + token.value + "_']").each(function() {
        var tokenText = this;
        var fieldset = $(this).parents('fieldset:first');
        if ($(fieldset).is('.collapsed')) {
          Drupal.toggleFieldset(fieldset);
        }
        if ($(token).is(':checked')) {
          $(this).parent().show();
          $('input[name*="op_types"]').not(':checked').each(function() {
            $("input[name*='_" + this.value + "_']").parent().hide();
          });
        }
        else {
          $(this).parent().fadeOut('normal');
        }
      });
    });

  });
}
