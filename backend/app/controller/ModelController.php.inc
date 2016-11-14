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
        $this->checkModelDoNotExist($model);
        
        $modelWithNewId = $this->dao->create($model);
        if (!$modelWithNewId) {
            throw new ControllerException(5, 500, "Error creating the new model with family '" . $model->getXid_family() . "', line '" . $model->getXid_line() . "', sex '" . $model->getXid_sex() . "' and variant '" . $model->getVariant() . "'.");
        }
        return $this->getById($modelWithNewId);
    }
    
    function updateModel($id, ModelDTO $model) {
        
        // Check the model with ID exists, if not it will raise exception
        $this->getById($id);
        
        $this->checkModelDoNotExist($model, $id);
        
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
    
    private function checkModelDoNotExist(ModelDTO $model, $idModel = null){
        $found = $this->dao->getByCode($model->getXid_family(), $model->getXid_line(), $model->getXid_sex(), $model->getVariant());
        if ( $found ){
            // If id_model is not set means the codes are for a new item; but if id_model
            // is set means is for an update, so I check the update is for the same id
            if (null === $idModel || $idModel !== $found['id_model']){ //checking for a creation
                throw new ControllerException(4, 409, "Already exists a model at the system with family '" . $model->getXid_family() . "', line '" . $model->getXid_line() . "', sex '" . $model->getXid_sex() . "' and variant '" . $model->getVariant() . "'.");
            }
        }
        return true;
    }
}
?>