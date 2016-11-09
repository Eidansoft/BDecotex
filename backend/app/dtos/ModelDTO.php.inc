<?php
require_once (dirname(__FILE__).'/BDecotexDTO.php.inc');
/**
 * Description of ModelDTO
 *
 * @author alex
 */
class ModelDTO extends BDecotexDTO {
    private $id_model;
    private $xid_family;
    private $xid_line;
    private $xid_sex;
    private $variant;
    private $description;
    private $front;
    private $back;
    private $neck;
    private $arm;
    private $observations;
    private $model_number_parent;
    private $xid_model_parent;
    private $creation_date;
    private $client;
    private $old_ref;
    
    function __construct($modelArray) {
        $sanitizeRules = array(
            'id_model'              => array('filter'    => FILTER_VALIDATE_INT,
                                             'options'   => array('min_range' => 0, 'max_range' => 2147483648)),
            'xid_family'            => array('filter'    => FILTER_VALIDATE_INT,
                                             'options'   => array('min_range' => 0, 'max_range' => 2147483648)),
            'xid_line'              => array('filter'    => FILTER_VALIDATE_INT,
                                             'options'   => array('min_range' => 0, 'max_range' => 2147483648)),
            'xid_sex'               => array('filter'    => FILTER_VALIDATE_INT,
                                             'options'   => array('min_range' => 0, 'max_range' => 2147483648)),
            'variant'               => array('filter'    => FILTER_VALIDATE_INT,
                                             'options'   => array('min_range' => 0, 'max_range' => 2147483648)),
            'description'           => array('filter'    => FILTER_SANITIZE_SPECIAL_CHARS,
                                             'flags'     => FILTER_FLAG_STRIP_LOW | FILTER_FLAG_ENCODE_HIGH),
            'front'                 => array('filter'    => FILTER_SANITIZE_SPECIAL_CHARS,
                                             'flags'     => FILTER_FLAG_STRIP_LOW | FILTER_FLAG_ENCODE_HIGH),
            'back'                  => array('filter'    => FILTER_SANITIZE_SPECIAL_CHARS,
                                             'flags'     => FILTER_FLAG_STRIP_LOW | FILTER_FLAG_ENCODE_HIGH),
            'neck'                  => array('filter'    => FILTER_SANITIZE_SPECIAL_CHARS,
                                             'flags'     => FILTER_FLAG_STRIP_LOW | FILTER_FLAG_ENCODE_HIGH),
            'arm'                   => array('filter'    => FILTER_SANITIZE_SPECIAL_CHARS,
                                             'flags'     => FILTER_FLAG_STRIP_LOW | FILTER_FLAG_ENCODE_HIGH),
            'observations'          => array('filter'    => FILTER_SANITIZE_SPECIAL_CHARS,
                                             'flags'     => FILTER_FLAG_STRIP_LOW | FILTER_FLAG_ENCODE_HIGH),
            'model_number_parent'   => array('filter'    => FILTER_SANITIZE_SPECIAL_CHARS,
                                             'flags'     => FILTER_FLAG_STRIP_LOW | FILTER_FLAG_ENCODE_HIGH),
            'xid_model_parent'      => array('filter'    => FILTER_VALIDATE_INT,
                                             'options'   => array('min_range' => 0, 'max_range' => 2147483648)),
            'creation_date'         => array('filter'    => FILTER_VALIDATE_INT,
                                             'options'   => array('min_range' => 0, 'max_range' => 4674407370955)),
            'client'                => array('filter'    => FILTER_SANITIZE_SPECIAL_CHARS,
                                             'flags'     => FILTER_FLAG_STRIP_LOW | FILTER_FLAG_ENCODE_HIGH),
            'old_ref'               => array('filter'    => FILTER_SANITIZE_SPECIAL_CHARS,
                                             'flags'     => FILTER_FLAG_STRIP_LOW | FILTER_FLAG_ENCODE_HIGH)
        );
        
        $sanitationAndValidationRules = [
            BDecotexDTO::SANITIZE_RULE_NAME => $sanitizeRules,
            'required'      => [['xid_family'], ['xid_line'], ['xid_sex'], ['variant']],
            'integer'       => [['id_model'], ['xid_family'], ['xid_line'], ['xid_sex'], ['variant'], ['xid_model_parent'], ['creation_date']],
            'lengthMin'      => [['description', 25]],
            'lengthMax'      => [['description', 250], ['front', 250], ['back', 250],
                                 ['neck', 250], ['arm', 250], ['observations', 5000],
                                 ['model_number_parent',50], ['client', 50], ['old_ref', 50]]
            ];

        parent::__construct($modelArray, $sanitationAndValidationRules);
        
    }
    
    protected function buildDto($modelArray) {
        
        if (isset($modelArray['id_model'])){
            $this->id_model = $modelArray['id_model'];
        }
        
        $this->xid_family = $modelArray['xid_family'];
        $this->xid_line = $modelArray['xid_line'];
        $this->xid_sex = $modelArray['xid_sex'];
        $this->variant = $modelArray['variant'];
        
        if (isset($modelArray['description'])){
            $this->description = $modelArray['description'];
        }
        if (isset($modelArray['front'])){
            $this->front = $modelArray['front'];
        }
        if (isset($modelArray['back'])){
            $this->back = $modelArray['back'];
        }
        if (isset($modelArray['neck'])){
            $this->neck = $modelArray['neck'];
        }
        if (isset($modelArray['arm'])){
            $this->arm = $modelArray['arm'];
        }
        if (isset($modelArray['observations'])){
            $this->observations = $modelArray['observations'];
        }
        if (isset($modelArray['model_number_parent'])){
            $this->model_number_parent = $modelArray['model_number_parent'];
        }
        if (isset($modelArray['xid_model_parent'])){
            $this->xid_model_parent = $modelArray['xid_model_parent'];
        }
        if (isset($modelArray['creation_date'])){
            $this->creation_date = $modelArray['creation_date'];
        }
        if (isset($modelArray['client'])){
            $this->client = $modelArray['client'];
        }
        if (isset($modelArray['old_ref'])){
            $this->old_ref = $modelArray['old_ref'];
        }
    }
    
    function getId_model() {
        return $this->id_model;
    }

    function getXid_family() {
        return $this->xid_family;
    }

    function getXid_line() {
        return $this->xid_line;
    }

    function getXid_sex() {
        return $this->xid_sex;
    }

    function getVariant() {
        return $this->variant;
    }

    function getDescription() {
        return $this->description;
    }

    function getFront() {
        return $this->front;
    }

    function getBack() {
        return $this->back;
    }

    function getNeck() {
        return $this->neck;
    }

    function getArm() {
        return $this->arm;
    }

    function getObservations() {
        return $this->observations;
    }

    function getModel_number_parent() {
        return $this->model_number_parent;
    }

    function getXid_model_parent() {
        return $this->xid_model_parent;
    }

    function getCreation_date() {
        return $this->creation_date;
    }

    function getClient() {
        return $this->client;
    }

    function getOld_ref() {
        return $this->old_ref;
    }

    function setId_model($id_model) {
        $this->id_model = $id_model;
    }

    function setXid_family($xid_family) {
        $this->xid_family = $xid_family;
    }

    function setXid_line($xid_line) {
        $this->xid_line = $xid_line;
    }

    function setXid_sex($xid_sex) {
        $this->xid_sex = $xid_sex;
    }

    function setVariant($variant) {
        $this->variant = $variant;
    }

    function setDescription($description) {
        $this->description = $description;
    }

    function setFront($front) {
        $this->front = $front;
    }

    function setBack($back) {
        $this->back = $back;
    }

    function setNeck($neck) {
        $this->neck = $neck;
    }

    function setArm($arm) {
        $this->arm = $arm;
    }

    function setObservations($observations) {
        $this->observations = $observations;
    }

    function setModel_number_parent($model_number_parent) {
        $this->model_number_parent = $model_number_parent;
    }

    function setXid_model_parent($xid_model_parent) {
        $this->xid_model_parent = $xid_model_parent;
    }

    function setCreation_date($creation_date) {
        $this->creation_date = $creation_date;
    }

    function setClient($client) {
        $this->client = $client;
    }

    function setOld_ref($old_ref) {
        $this->old_ref = $old_ref;
    }


}
