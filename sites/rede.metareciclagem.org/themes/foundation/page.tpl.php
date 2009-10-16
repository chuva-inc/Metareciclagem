<?php /* $Id: page.tpl.php,v 1.4 2008/07/14 01:41:22 add1sun Exp $ */ ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language->language; ?>" xml:lang="<?php print $language->language; ?>">
<head>
 <title><?php print $head_title; ?></title>
 <?php print $head; ?>
 <?php print $styles; ?>
 <?php print $scripts; ?>
 <script type="text/javascript"> </script>
</head>
<body class="<?php print $body_classes; ?>">

  <div id="header">
    <h1>
      <?php if ($logo): ?>
      <a href="<?php print $front_page; ?>"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" class="logo" /></a>
      <?php endif; ?>

      <?php if ($site_name): ?>
      <span class="site-name"><a href="<?php print $front_page; ?>"><?php print $site_name; ?></a></span>
      <?php endif; ?>

      <?php if ($site_slogan): ?>
      <span class="site-slogan"><?php print $site_slogan; ?></span>
      <?php endif; ?>
    </h1>

    <?php if ($primary_links || $secondary_links): ?>
    <div class="navigation">
      <?php if ($primary_links): ?>
      <div class="navigation-primary">
        <?php print theme('links', $primary_links); ?>
      </div>
      <?php endif; ?>

      <?php if ($secondary_links): ?>
      <div class="navigation-secondary">
        <?php print theme('links', $secondary_links); ?>
      </div>
      <?php endif; ?>
    </div>
    <?php endif; ?>

    <?php if ($search_box): ?>
    <?php print $search_box; ?>
    <?php endif; ?>

    <?php print $header; ?>
  </div>

  <div id="container" class="clear-block">
    <?php if ($left): ?>
    <div id="left-sidebar" class="sidebar"><?php print $left; ?></div>
    <?php endif; ?>

    <div id="page">
      <?php if ($breadcrumb): ?>
      <?php print $breadcrumb; ?>
      <?php endif; ?>

      <?php if ($messages): ?>
      <?php print $messages; ?>
      <?php endif; ?>

      <?php print $contenttop; ?>

      <?php if ($is_front && $mission): ?>
      <div class="mission"><?php print $mission; ?></div>
      <?php endif; ?>

      <?php if ($title): ?>
      <h2 class="title"><?php print $title; ?></h2>
      <?php endif; ?>

      <?php if ($help): ?>
      <div class="help"><?php print $help; ?></div>
      <?php endif; ?>

      <?php if ($tabs): ?>
      <?php print $tabs; ?>
      <?php endif; ?>

      <?php print $content; ?>
    </div>

    <?php if ($right): ?>
    <div id="right-sidebar" class="sidebar"><?php print $right; ?></div>
    <?php endif; ?>
  </div>

  <div id="footer">
    <?php if ($footer_message): ?><?php print $footer_message; ?><?php endif; ?>
    <?php if ($footer): ?><?php print $footer; ?><?php endif; ?>
  </div>

  <?php print $closure; ?>
</body>
</html>

