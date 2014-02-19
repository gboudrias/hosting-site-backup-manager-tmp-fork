<?php

function drush_hosting_backup_nogzip_pre_hosting_task($task) {
  $task = &drush_get_context('HOSTING_TASK'); 

  $nogzip = $task->task_args['nogzip'];

  if (isset($nogzip)) {
    $task->options['nogzip'] = $nogzip;
  }
}

/**
 * Implementation of hook_hosting_post_backup
 *
 * Checks to see if gzipping is disabled in the options.
 */
function drush_hosting_backup_nogzip_pre_provision_backup($url = NULL) {
  $backup_file = drush_get_option('backup_file');
  $nogzip = drush_get_option('nogzip');

  if ($nogzip && substr($backup_file, -3) == '.gz') {
    drush_log('Nogzip option selected. Foregoing gzip.');
    // Truncate the '.gz' so that the backup isn't gzipped
    $new_file_name = substr($backup_file, 0, strlen($backup_file) - 3);

    drush_set_option('backup_file', $new_file_name);
  }
}
