<?php
require_once "../model/ModelDAOImpl.php.inc";
require_once (dirname(__FILE__)."/../model/FamilyDAOImpl.php.inc");
require_once (dirname(__FILE__)."/../model/LineDAOImpl.php.inc");
require_once (dirname(__FILE__)."/../model/SexDAOImpl.php.inc");
require_once "../model/BDecotexException.php.inc";
require_once (dirname(__FILE__).'/BDecotexController.php.inc');

class ModelController extends BDecotexController {

    private $familyDao;
    private $lineDao;
    private $sexDao;
    
    function __construct() {
        parent::__construct(new ModelDAOImpl());
        $this->familyDao = new FamilyDAOImpl();
        $this->lineDao = new LineDAOImpl();
        $this->sexDao = new SexDAOImpl();
    }

    function createModel($family, $line, $sex, $variant) {
        $this->checkModelMandatoryFields($family, $line, $sex, $variant);
        
        $this->checkCodeNotDuplicate($family, $line, $sex, $variant);
        
        $newId = $this->dao->create($family, $line, $sex, $variant);
        if (!$newId) {
            throw new BDecotexException(5, 500, "Error creating the new model with family '$family', line '$line', sex '$sex' and variant '$variant'.");
        }
        return $this->getById($newId);
    }
    
    function updateModel($id, $name, $code) {
        $this->checkModelMandatoryFields($name, $code);
        
        $this->checkCodeNotDuplicate($code, $id);
        
        // Check the model with ID exists, if not it will raise exception
        $this->getById($id);
        
        $res = $this->dao->update($id, $name, $code);
        if (!$res) {
            throw new BDecotexException(5, 500, "Error updating the model with ID: '$id'");
        }
        return $this->getById($id);
    }
    
    private function checkModelMandatoryFields($family, $line, $sex, $variant){
        if ($family == NULL || trim($family) == "") {
            throw new BDecotexException(4, 404, "The 'family' is mandatory");
        } else if ( ! $this->familyDao->getById($family)){
            throw new BDecotexException(4, 404, "The 'family' id provided '$family' is not valid");
        }
        
        if ($line == NULL || trim($line) == "") {
            throw new BDecotexException(4, 404, "The 'line' is mandatory");
        } else if ( ! $this->lineDao->getById($line)){
            throw new BDecotexException(4, 404, "The 'line' id provided '$line' is not valid");
        }
        
        if ($sex == NULL || trim($sex) == "") {
            throw new BDecotexException(4, 404, "The 'sex' is mandatory");
        } else if ( ! $this->sexDao->getById($sex)){
            throw new BDecotexException(4, 404, "The 'sex' id provided '$sex' is not valid");
        }
        
        if ($variant == NULL || trim($variant) == "") {
            throw new BDecotexException(4, 404, "The 'variant' is mandatory");
        }
        return true;
    }
    
    private function checkCodeNotDuplicate($family, $line, $sex, $variant){
        $found = $this->dao->getByCode($family, $line, $sex, $variant);
        if ( $found ){
            throw new BDecotexException(4, 409, "Already exists a model at the system with family '$family', line '$line', sex '$sex' and variant '$variant'.");
        }
        return true;
    }
}
?>