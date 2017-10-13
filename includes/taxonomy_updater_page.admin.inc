<?php
/**
 * Implements hook_form().
 */
function update_terms_form($form, &$form_state, $vocabulary) {

	$wrappername = 'form_fields_container';
	$weight = 0;

  $form[$wrappername] = array(
    '#type' => 'container',
    '#prefix' => '<div class="'.$wrappername.'">',
    '#suffix' => '</div>',
  );

  $weight++;
  $form[$wrappername]['message'] = array(
  	'#type' => 'item',
  	'#markup' => '<div class="messages warning">Warning, database loading may increase during updating so please be patient.</div>',
  	'#weight' => $weight,
  );

  $weight++;
  $form[$wrappername]['vid'] = array(
  	'#type' => 'value',
  	'#value' => $vocabulary->vid,
  	'#weight' => $weight,
  );

  $weight++;
  $form[$wrappername]['name'] = array(
  	'#type' => 'value',
  	'#value' => $vocabulary->name,
  	'#weight' => $weight,
  );

  $weight++;
  $form[$wrappername]['submit'] = array(
  	'#type' => 'submit',
  	'#value' => 'Update terms',
  	'#name' => 'op',
  	'#prefix' => '<div class="form-actions">',
  	'#suffix' => '</div>',
  	'#weight' => $weight,
  );

  return $form;
}


/**
 * submit process for update_terms_form
 */
function update_terms_form_submit($form, &$form_state) {
	if (isset($form_state['values'])) {
		$values = $form_state['values'];

		if (isset($values['vid']) && isset($values['name'])) {
			$vid = $values['vid'];
			$name = $values['name'];
			$terms = taxonomy_get_tree($vid, 0, NULL, TRUE);

			foreach ($terms as $term) {
				taxonomy_term_save($term);
			}

			drupal_set_message(t(count($terms).' term(s) on <em><strong>' . $name . '</strong></em> vobulary has been updated.'), 'status');
		}
	}
}