<?php
require_once (dirname(__FILE__).'/../model/FamilyDAOImpl.php.inc');
require_once (dirname(__FILE__).'/ControllerException.php.inc');
require_once (dirname(__FILE__).'/BDecotexController.php.inc');
require_once (dirname(__FILE__).'/../dtos/FamilyDTO.php.inc');

class FamilyController extends BDecotexController {

    function __construct() {
        parent::__construct(new FamilyDAOImpl());
    }

    function createFamily(FamilyDTO $family) {
        $this->checkCodeNotDuplicate($family);
        
        $newId = $this->dao->create($family);
        if (!$newId) {
            throw new ControllerException(5, 500, "Error creating the new family '" . $family->getDescription() . "'");
        }
        return $this->getById($newId);
    }
    
    function updateFamily($id, FamilyDTO $family) {
        $this->checkCodeNotDuplicate($family, $id);
        
        // Check the family with ID exists, if not it will raise exception
        $this->getById($id);
        
        $res = $this->dao->update($id, $family);
        if (!$res) {
            throw new ControllerException(5, 500, "Error updating the family with ID: '$id'");
        }
        return $this->getById($id);
    }
    
    private function checkCodeNotDuplicate(FamilyDTO $family, $id = null){
        $found = $this->dao->getByCode($family->getCode());
        if ( $found ){
            // dependiendo del ID, si es nulo, es que se intenta crear, en c.c. es una modificacion
            if (null === $id || $id !== $found['id_family']){
                throw new ControllerException(4, 409, "The code '" . $family->getCode() . "' already exists");
            }
        }
        return true;
    }
}
?>