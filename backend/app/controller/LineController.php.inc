<?php
require_once "../model/LineDAOImpl.php.inc";
require_once "../model/BDecotexException.php.inc";
require_once (dirname(__FILE__).'/BDecotexController.php.inc');

class LineController extends BDecotexController {

    function __construct() {
        parent::__construct(new LineDAOImpl());
    }

    function createLine($name, $code) {
        $this->checkLineMandatoryFields($name, $code);
        
        $this->checkCodeNotDuplicate($code);
        
        $newId = $this->dao->create($name, $code);
        if (!$newId) {
            throw new BDecotexException(5, 500, "Error creating the new line '$name'");
        }
        return $this->getById($newId);
    }
    
    function updateLine($id, $name, $code) {
        $this->checkLineMandatoryFields($name, $code);
        
        $this->checkCodeNotDuplicate($code, $id);
        
        // Check the line with ID exists, if not it will raise exception
        $this->getById($id);
        
        $res = $this->dao->update($id, $name, $code);
        if (!$res) {
            throw new BDecotexException(5, 500, "Error updating the line with ID: '$id'");
        }
        return $this->getById($id);
    }
    
    private function checkLineMandatoryFields($name, $code){
        if ($name == NULL || trim($name) == "") {
            throw new BDecotexException(4, 404, "The 'name' is mandatory");
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
            } else if ($id != $found['id_line']){
                throw new BDecotexException(4, 409, "The code '$code' already exists");
            }
        }
        return true;
    }
}
?>