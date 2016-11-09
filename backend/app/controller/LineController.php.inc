<?php
require_once (dirname(__FILE__).'/../model/LineDAOImpl.php.inc');
require_once (dirname(__FILE__).'/ControllerException.php.inc');
require_once (dirname(__FILE__).'/BDecotexController.php.inc');
require_once (dirname(__FILE__).'/../dtos/LineDTO.php.inc');

class LineController extends BDecotexController {

    function __construct() {
        parent::__construct(new LineDAOImpl());
    }

    function createLine(LineDTO $line) {
        $this->checkCodeNotDuplicate($line);
        
        $newId = $this->dao->create($line);
        if (!$newId) {
            throw new ControllerException(5, 500, "Error creating the new line '" . $line->getName() . "'");
        }
        return $this->getById($newId);
    }
    
    function updateLine($id, LineDTO $line) {
        $this->checkCodeNotDuplicate($line, $id);
        
        // Check the line with ID exists, if not it will raise exception
        $this->getById($id);
        
        $res = $this->dao->update($id, $line);
        if (!$res) {
            throw new ControllerException(5, 500, "Error updating the line with ID: '$id'");
        }
        return $this->getById($id);
    }
    
    private function checkCodeNotDuplicate(LineDTO $line, $id = null){
        $found = $this->dao->getByCode($line->getCode());
        if ( $found ){
            // dependiendo del ID, si es nulo, es que se intenta crear, en c.c. es una modificacion
            if (null === $id || $id !== $found['id_line']){
                throw new ControllerException(4, 409, "The code '" . $line->getCode() . "' already exists");
            }
        }
        return true;
    }
}
?>