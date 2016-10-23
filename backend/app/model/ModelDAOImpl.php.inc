<?php
require_once (dirname(__FILE__).'/BDecotexDAOImpl.php.inc');
require_once (dirname(__FILE__).'/../dtos/ModelDTO.php.inc');

class ModelDAOImpl extends BDecotexDAOImpl {
    
    public function __construct() {
        parent::__construct('model');
    }
    
    public function create(ModelDTO $model) {
        $datetime1 = new DateTime;
        $query = "INSERT INTO $this->table_name ("
            . (null !== $model->getXid_family() ? " xid_family, " : "")
            . (null !== $model->getXid_line() ? " xid_line, " : "")
            . (null !== $model->getXid_sex() ? " xid_sex, " : "")
            . (null !== $model->getVariant() ? " variant, " : "")
            . "creation_date "
        . ") VALUES ("
            . (null !== $model->getXid_family() ? $model->getXid_family() . ", " : "")
            . (null !== $model->getXid_line() ? $model->getXid_line() . ", " : "")
            . (null !== $model->getXid_sex() ? $model->getXid_sex() . ", " : "")
            . (null !== $model->getVariant() ? $model->getVariant() . ", " : "")
            . $datetime1->getTimestamp()
        . ")";
        $newModelId = $this->getModifiedIdExecutingQuery($query);
        return $this->update($newModelId, $model);
    }
    
    public function update($id, ModelDTO $model) {
        $query = "UPDATE $this->table_name "
        . " SET "
            . (null !== $model->getXid_family() ? " xid_family = " . $model->getXid_family() . ", " : "")
            . (null !== $model->getXid_line() ? " xid_line = " . $model->getXid_line() . ", " : "")
            . (null !== $model->getXid_sex() ? " xid_sex = " . $model->getXid_sex() . ", " : "")
            . (null !== $model->getVariant() ? " variant = " . $model->getVariant() . ", " : "")
            . (null !== $model->getDescription() ? " description = " . $model->getDescription() . ", " : "")
            . (null !== $model->getFront() ? " front = " . $model->getFront() . ", " : "")
            . (null !== $model->getBack() ? " back = " . $model->getBack() . ", " : "")
            . (null !== $model->getNeck() ? " neck = " . $model->getNeck() . ", " : "")
            . (null !== $model->getArm() ? " arm = " . $model->getArm() . ", " : "")
            . (null !== $model->getObservations() ? " observations = " . $model->getObservations() . ", " : "")
            . (null !== $model->getModel_number_parent() ? " model_number_parent = " . $model->getModel_number_parent() . ", " : "")
            . (null !== $model->getXid_model_parent() ? " xid_model_parent = " . $model->getXid_model_parent() . ", " : "")
            //. (null !== $model->getCreation_date() ? " creation_date = " . $model->getCreation_date() . ", " : "")
            . (null !== $model->getClient() ? " client = " . $model->getClient() . ", " : "")
            . (null !== $model->getOld_ref() ? " old_ref = " . $model->getOld_ref() . ", " : "");
        $query = substr($query, 0, strlen($query)-2); //remove last coma
        $query .= " WHERE id_$this->table_name = $id";
        return $this->executeQuery($query);
    }
    
    public function getByCode($family, $line, $sex, $variant) {
        return $this->getSingleResult("SELECT * "
                                    . "FROM $this->table_name "
                                    . "WHERE xid_family = $family "
                                    . "AND xid_line = $line "
                                    . "AND xid_sex = $sex "
                                    . "AND variant = $variant");
    }
}
?>