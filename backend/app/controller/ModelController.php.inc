<?php
require_once "../model/ModelDAOImpl.php.inc";
require_once (dirname(__FILE__)."/../model/FamilyDAOImpl.php.inc");
require_once (dirname(__FILE__)."/../model/LineDAOImpl.php.inc");
require_once (dirname(__FILE__)."/../model/SexDAOImpl.php.inc");
require_once "../model/BDecotexException.php.inc";
require_once (dirname(__FILE__).'/BDecotexController.php.inc');

class ModelController extends BDecotexController {

    const ATTR_FAMILY = 0;
    const ATTR_LINE = 1;
    const ATTR_SEX = 2;
    const ATTR_VARIANT = 3;
    
    public $mandatoryAttributes = array("xid_family" => ModelCo,
                                 "xid_line",
                                 "xid_sex",
                                 "variant");
    public $allAttributes = array("xid_family",
                                 "xid_line",
                                 "xid_sex",
                                 "variant",
                                 "description",
                                 "front",
                                 "back",
                                 "neck",
                                 "arm",
                                 "observations",
                                 "model_number_parent",
                                 "xid_model_parent",
                                 "creation_date",
                                 "client",
                                 "old_ref");
    
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
    
    function updateModel($id, $attribute, $value) {
        $this->checkModelUpdateMandatoryFields($attribute, $value);
        
        // Check the model with ID exists, if not it will raise exception
        $modelToUpdate = $this->getById($id);
        
        if ($attribute == "xid_family"){
            $this->checkCodeNotDuplicate($value, $modelToUpdate['xid_line'], $modelToUpdate['xid_sex'], $modelToUpdate['variant'], $modelToUpdate['id_model']);
        } else if ($attribute == "xid_line"){
            $this->checkCodeNotDuplicate($modelToUpdate['xid_family'], $value, $modelToUpdate['xid_sex'], $modelToUpdate['variant'], $modelToUpdate['id_model']);
        } else if ($attribute == "xid_sex"){
            $this->checkCodeNotDuplicate($modelToUpdate['xid_family'], $modelToUpdate['xid_line'], $value, $modelToUpdate['variant'], $modelToUpdate['id_model']);
        } else if ($attribute == "variant"){
            $this->checkCodeNotDuplicate($modelToUpdate['xid_family'], $modelToUpdate['xid_line'], $modelToUpdate['xid_sex'], $value, $modelToUpdate['id_model']);
        }
        
        $res = $this->dao->update($id, $attribute, $value);
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
    
    private function checkModelUpdateMandatoryFields($attribute, $value){        
        if ($attribute == NULL || trim($attribute) == "") {
            throw new BDecotexException(4, 404, "The 'attribute' is mandatory");
        } else if ( ! in_array($attribute, $this->allAttributes)){
            throw new BDecotexException(4, 404, "The 'attribute' provided '$attribute' is not valid");
        }
        
        if ($value == NULL || trim($value) == "") {
            throw new BDecotexException(4, 404, "The 'value' is mandatory");
        }
    }
    
    private function checkCodeNotDuplicate($family, $line, $sex, $variant, $id = null){
        $found = $this->dao->getByCode($family, $line, $sex, $variant);
        if ( $found ){
            if ($id == null || $id != $found['id_model']){ //checking for a creation
                throw new BDecotexException(4, 409, "Already exists a model at the system with family '$family', line '$line', sex '$sex' and variant '$variant'.");
            }
        }
        return true;
    }
}
?>