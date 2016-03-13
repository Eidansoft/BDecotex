<?php
require_once (dirname(__FILE__).'/BDecotexDAOImpl.php.inc');

class ModelDAOImpl extends BDecotexDAOImpl {
    
    public function __construct() {
        parent::__construct('model');
    }
    
    public function create($familyId, $lineId, $sexId, $variant,
            $description, $front, $back, $neck, $arm, $observations,
            $oldModelNumber, $parentModelId, $creationDate = "NOW()") {
        return $this->getModifiedIdExecutingQuery("INSERT INTO $this->table_name ("
                                                    . "xid_family, "
                                                    . "xid_line, "
                                                    . "xid_sex, "
                                                    . "variant, "
                                                    . "description, "
                                                    . "front, "
                                                    . "back, "
                                                    . "neck, "
                                                    . "arm, "
                                                    . "observations, "
                                                    . "old_model_number, "
                                                    . "xid_model_parent, "
                                                    . "creation_date "
                                                 . ") VALUES ("
                                                    . "$familyId, "
                                                    . "$lineId, "
                                                    . "$sexId, "
                                                    . "$variant, "
                                                    . "$description, "
                                                    . "$front, "
                                                    . "$back, "
                                                    . "$neck, "
                                                    . "$arm, "
                                                    . "$observations, "
                                                    . "$oldModelNumber, "
                                                    . "$parentModelId, "
                                                    . "$creationDate "
                                                 . ")");
    }

    public function update($id, $description) {
        return $this->executeQuery("UPDATE $this->table_name "
                                 . "SET description = '$description' "
                                 . "WHERE id_$this->table_name = $id");
    }
}
?>