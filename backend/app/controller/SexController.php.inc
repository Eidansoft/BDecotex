<?php
require_once (dirname(__FILE__).'/../model/SexDAOImpl.php.inc');
require_once (dirname(__FILE__).'/ControllerException.php.inc');
require_once (dirname(__FILE__).'/BDecotexController.php.inc');

class SexController extends BDecotexController {

    function __construct() {
        parent::__construct(new SexDAOImpl());
    }

    function createSex(SexDTO $sex) {
        
        $this->checkCodeNotDuplicate($sex);
        
        $newId = $this->dao->create($sex);
        if (!$newId) {
            throw new ControllerException(5, 500, "Error creating the new sex '" . $sex->getName() . "'");
        }
        return $this->getById($newId);
    }
    
    function updateSex($id, SexDTO $sex) {
        $this->checkCodeNotDuplicate($sex, $id);
        
        // Check the sex with ID exists, if not it will raise exception
        $this->getById($id);
        
        $res = $this->dao->update($id, $sex);
        if (!$res) {
            throw new ControllerException(5, 500, "Error updating the sex with ID: '" . $sex->getId_sex() . "'");
        }
        return $this->getById($id);
    }
    
    private function checkCodeNotDuplicate(SexDTO $sex, $id = null){
        $found = $this->dao->getByCode($sex->getCode());
        if ( $found ){
            // dependiendo del ID, si es nulo, es que se intenta crear, en c.c. es una modificacion
            if (null === $id || $id !== $found['id_sex']){
                throw new ControllerException(4, 409, "The code '" . $sex->getCode() . "' already exists");
            }
        }
        return true;
    }
}
?>