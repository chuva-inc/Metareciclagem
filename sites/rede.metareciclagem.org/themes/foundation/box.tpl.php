<?php /* $Id: box.tpl.php,v 1.1 2006/06/28 18:31:05 rkerr Exp $ */ ?>
<div class="box">
  <?php if ($title): ?>
  <h3 class="title"><?php print $title; ?></h3>
  <?php endif; ?>

  <div class="content"><?php print $content; ?></div>
</div>
