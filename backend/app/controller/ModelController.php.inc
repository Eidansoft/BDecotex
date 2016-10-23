<?php
require_once (dirname(__FILE__).'/../model/ModelDAOImpl.php.inc');
require_once (dirname(__FILE__).'/../model/FamilyDAOImpl.php.inc');
require_once (dirname(__FILE__).'/../model/LineDAOImpl.php.inc');
require_once (dirname(__FILE__).'/../model/SexDAOImpl.php.inc');
require_once (dirname(__FILE__).'/ControllerException.php.inc');
require_once (dirname(__FILE__).'/BDecotexController.php.inc');
require_once (dirname(__FILE__).'/../model/DAOException.php.inc');
require_once (dirname(__FILE__).'/../dtos/ModelDTO.php.inc');

class ModelController extends BDecotexController {

    const ATTR_FAMILY = 0;
    const ATTR_LINE = 1;
    const ATTR_SEX = 2;
    const ATTR_VARIANT = 3;
    
    public $mandatoryAttributes = array("xid_family",
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
        parent::__construct(new ModelDAOImpl);
        $this->familyDao = new FamilyDAOImpl;
        $this->lineDao = new LineDAOImpl;
        $this->sexDao = new SexDAOImpl;
    }

    function createModel(ModelDTO $model) {
        //$this->checkModelMandatoryFields($family, $line, $sex, $variant);
        
        $this->checkModelDoNotExist($model);
        
        $modelWithNewId = $this->dao->create($model);
        if (!$modelWithNewId) {
            throw new ControllerException(5, 500, "Error creating the new model with family '" . $model->getXid_family() . "', line '" . $model->getXid_line() . "', sex '" . $model->getXid_sex() . "' and variant '" . $model->getVariant() . "'.");
        }
        return $this->getById($modelWithNewId);
    }
    
    function updateModel($id, ModelDTO $model) {
        //$this->checkModelUpdateMandatoryFields($attribute, $value);
        
        // Check the model with ID exists, if not it will raise exception
        $modelToUpdate = $this->getById($id);
        
        $this->checkModelDoNotExist($model);
        
        //check xid_model_parent must exist
        if (null !== $model->getXid_model_parent()){
            // Check the model with ID exists, if not it will raise exception
            try {
                $this->getById($model->getXid_model_parent());
            } catch (DAOException $ex){
                throw new ControllerException($ex->getCode(), $ex->getHttpCode(), "The parent model referenced with ID '$value' does not exist");
            }
        }
        
        $res = $this->dao->update($id, $model);
        if (!$res) {
            throw new ControllerException(5, 500, "Error updating the model with ID: '$id'");
        }
        return $this->getById($id);
    }
    
//    private function checkModelMandatoryFields($family, $line, $sex, $variant){
//        if ($family == NULL || trim($family) == "") {
//            throw new ControllerException(4, 404, "The 'family' is mandatory");
//        } else if ( ! $this->familyDao->getById($family)){
//            throw new ControllerException(4, 404, "The 'family' id provided '$family' is not valid");
//        }
//        
//        if ($line == NULL || trim($line) == "") {
//            throw new ControllerException(4, 404, "The 'line' is mandatory");
//        } else if ( ! $this->lineDao->getById($line)){
//            throw new ControllerException(4, 404, "The 'line' id provided '$line' is not valid");
//        }
//        
//        if ($sex == NULL || trim($sex) == "") {
//            throw new ControllerException(4, 404, "The 'sex' is mandatory");
//        } else if ( ! $this->sexDao->getById($sex)){
//            throw new ControllerException(4, 404, "The 'sex' id provided '$sex' is not valid");
//        }
//        
//        if ($variant == NULL || trim($variant) == "") {
//            throw new ControllerException(4, 404, "The 'variant' is mandatory");
//        }
//        return true;
//    }
    
//    private function checkModelUpdateMandatoryFields($attribute, $value){        
//        if ($attribute == NULL || trim($attribute) == "") {
//            throw new ControllerException(4, 404, "The 'attribute' is mandatory");
//        } else if ( ! in_array($attribute, $this->allAttributes)){
//            throw new ControllerException(4, 404, "The 'attribute' provided '$attribute' is not valid");
//        }
//        
//        if ($value == NULL || trim($value) == "") {
//            throw new ControllerException(4, 404, "The 'value' is mandatory");
//        }
//    }
    
    private function checkModelDoNotExist(ModelDTO $model){
        $found = $this->dao->getByCode($model->getXid_family(), $model->getXid_line(), $model->getXid_sex(), $model->getVariant());
        if ( $found ){
            // If id_model is not set means the codes are for a new item; but if id_model
            // is set means is for an update, so I check the update is for the same id
            if (null !== $model->getId_model() || $model->getId_model() !== $found['id_model']){ //checking for a creation
                throw new ControllerException(4, 409, "Already exists a model at the system with family '$family', line '$line', sex '$sex' and variant '$variant'.");
            }
        }
        return true;
    }
}
?>