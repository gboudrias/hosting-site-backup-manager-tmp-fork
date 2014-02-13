<?php

function drush_hosting_backup_nogzip_pre_hosting_task($task) {
  $task = &drush_get_context('HOSTING_TASK'); 

  $nogzip = $task->task_args['nogzip'];

  if (isset($nogzip)) {
    $process = &drush_get_context('process'); 
    drush_set_option('nogzip', $nogzip);

    $process['nogzip'] = $nogzip;
    
    drush_log('Setting nogzip: ' . $task->task_args['nogzip']);
    drush_log('Settings: ' . implode(' --- ', array_keys($task->task_args)));
  }
}



/**
 * Implementation of hook_hosting_post_backup
 *
 * Checks to see if gzipping is disabled in the options.
 */
function drush_hosting_backup_nogzip_pre_provision_backup($url = NULL) {
  $context = d();
//  $siteinfo = d();
  $backup_file = drush_get_option('backup_file');
  $nogzip = drush_get_option('nogzip');

  drush_log('Nogzip: ' . $nogzip);
  drush_log('Name: ' . $context->name);

  drush_log(implode(' --- ', array_keys(get_object_vars($context))));
  /*
  drush_log('arguments' . implode(' --- ', array_keys($context['arguments'])));
  drush_log($context['arguments'][0]);
  drush_log('site: ' . implode(' --- ', array_keys($context['site'])));
  drush_log('process' . implode(' --- ', array_keys($context['process'])));

  drush_log('Nogzip option? : ' . implode(' --- ', drush_get_context_options('nogzip', TRUE)));
*/

  return;

  if (!empty($site) && $task>type == 'site') {
    $nogzip = $task->task_args['nogzip'];

    foreach (get_object_vars($task) as $key => $val) {
      if (is_array($val)) {
        drush_log("---$key---");
      }
    }

    drush_log('Option: ' .   $nogzip);
    drush_log($backup_file);

    return;

    if (substr($backup_file, -3) == '.gz') {
      // Truncate the '.gz' so that the backup isn't gzipped
      $new_file_name = substr($backup_file, 0, strlen($backup_file) - 3);

      drush_log('New name: ' . $new_file_name);

      drush_set_option('backup_file', $new_file_name);
    }
  }
}
