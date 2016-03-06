<?php
require_once "../model/FamilyDAOImpl.php.inc";
require_once "../model/BDecotexException.php.inc";
require_once (dirname(__FILE__).'/BDecotexController.php.inc');
//require_once "./BDecotexController.php.inc";

class FamilyController extends BDecotexController {

    function __construct() {
        parent::__construct(new FamilyDAOImpl());
    }

    function createFamily($description) {
        if ($description == NULL || trim($description) == "") {
            throw new BDecotexException(4, 404, "The description is mandatory to create a new family");
        }
        $res = $this->dao->create($description);
        if (!$res) {
            throw new BDecotexException(5, 500, "Error creating the new family '$description'");
        }
    }
    
    function updateFamily($id, $description) {
        // Check the family with ID exists, if not it will raise exception
        $this->getById($id);
        if ($description == NULL || trim($description) == "") {
            throw new BDecotexException(4, 404, "The description is mandatory to update the family with ID: '$id'");
        }
        
        $res = $this->dao->update($id, $description);
        if (!$res) {
            throw new BDecotexException(5, 500, "Error updating the family with ID: '$id'");
        }
    }
}
?>