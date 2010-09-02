<?php /* $Id: block.tpl.php,v 1.1 2006/06/28 18:31:05 rkerr Exp $ */ ?>
<div id="block-<?php print $block->module; ?>-<?php print $block->delta; ?>" class="block<?php print " block-$block->module"; ?>">
  <?php if ($block->subject): ?>
  <div class="title"><?php print $block->subject; ?></div>
  <?php endif; ?>

  <div class="content"><?php print $block->content; ?></div>
</div>

