<?php /* $Id: node.tpl.php,v 1.3 2008/06/22 20:49:49 add1sun Exp $ */ ?>
<div id="node-<?php print $node->nid; ?>" class="node<?php print " node-" . $node->type; ?><?php print ($sticky) ? " node-sticky" : ""; ?>">
  <?php if (!$page && $title): ?>
  <h3 class="title"><a href="<?php print $node_url; ?>" title="<?php print $title; ?>"><?php print $title; ?></a></h3>
  <?php endif; ?>

  <?php print $picture; ?>

  <?php if ($submitted): ?>
  <div class="date"><?php print $date; ?></div>
  <div class="author"><?php print $authored; ?></div>
  <?php endif; ?>

  <div class="terms"><?php print $terms; ?></div>

  <div class="content"><?php print $content; ?></div>

  <div class="links"><?php print $links; ?></div>
</div>

