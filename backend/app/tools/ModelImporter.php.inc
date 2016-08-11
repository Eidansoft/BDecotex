<?php
require_once (dirname(__FILE__).'/BDecotexImporter.php.inc');
require_once '../model/ModelDAOImpl.php.inc';
require_once '../model/FamilyDAOImpl.php.inc';
require_once '../model/LineDAOImpl.php.inc';
require_once '../model/SexDAOImpl.php.inc';

/**
 * Description of ModelImporter
 *
 * @author alex
 */
class ModelImporter extends BDecotexImporter {
    
    public function __construct() {
        parent::__construct(realpath(dirname(__FILE__)."/../../../originales/Nuevos_Modelos.xml"), new ModelDAOImpl());
    }

    protected function processObject($object) {
        $familyDAO = new FamilyDAOImpl();
        $lineDAO = new LineDAOImpl();
        $sexDAO = new SexDAOImpl();
        
        $this->dao->create($familyDAO->getByCode($object->Tipo_prenda)['id_family'],
                            $lineDAO->getByCode($object->Lineas)['id_line'],
                            $sexDAO->getByCode($object->Sexo)['id_sex'],
                            ($object->var == '' ? 0 : $object->var),
                            $object->D_basica,
                            $object->Delantero,
                            $object->Espalda_Traser,
                            $object->Cuello,
                            $object->Manga,
                            $object->Observaciones,
                            null,
                            null,
                            $object->Num_mod,
                            $object->P_base
                            );
    }

}
