<?php
require_once (dirname(__FILE__).'/../model/FamilyDAOImpl.php.inc');
require_once (dirname(__FILE__).'/../model/BDecotexException.php.inc');
require_once (dirname(__FILE__).'/BDecotexController.php.inc');
//require_once "./BDecotexController.php.inc";

class FamilyController extends BDecotexController {

    function __construct() {
        parent::__construct(new FamilyDAOImpl());
    }

    function createFamily($description, $code) {
        $this->checkFamilyMandatoryFields($description, $code);
        
        $this->checkCodeNotDuplicate($code);
        
        $newId = $this->dao->create($description, $code);
        if (!$newId) {
            throw new BDecotexException(5, 500, "Error creating the new family '$description'");
        }
        return $this->getById($newId);
    }
    
    function updateFamily($id, $description, $code) {
        $this->checkFamilyMandatoryFields($description, $code);
        
        $this->checkCodeNotDuplicate($code, $id);
        
        // Check the family with ID exists, if not it will raise exception
        $this->getById($id);
        
        $res = $this->dao->update($id, $description, $code);
        if (!$res) {
            throw new BDecotexException(5, 500, "Error updating the family with ID: '$id'");
        }
        return $this->getById($id);
    }
    
    private function checkFamilyMandatoryFields($description, $code){
        if ($description == NULL || trim($description) == "") {
            throw new BDecotexException(4, 404, "The 'description' is mandatory");
        }
        if ($code == NULL || trim($code) == "") {
            throw new BDecotexException(4, 404, "The 'code' is mandatory");
        }
        return true;
    }
    
    private function checkCodeNotDuplicate($code, $id = null){
        $found = $this->dao->getByCode($code);
        if ( $found ){
            // dependiendo del ID, si es nulo, es que se intenta crear, en c.c. es una modificacion
            if ($id == null){
                throw new BDecotexException(4, 409, "The code '$code' already exists");
            } else if ($id != $found['id_family']){
                throw new BDecotexException(4, 409, "The code '$code' already exists");
            }
        }
        return true;
    }
}
?>