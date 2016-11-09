<?php
require_once (dirname(__FILE__).'/CommonContextFunctions.php');
require_once (dirname(__FILE__).'/FamilyContext.php');
require_once (dirname(__FILE__).'/LineContext.php');
require_once (dirname(__FILE__).'/SexContext.php');
require_once (dirname(__FILE__).'/../../httpCallsAPI.php');

use Behat\Behat\Tester\Exception\PendingException;
use Behat\Behat\Context\Context;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;

/**
 * Defines application features from the Model context.
 */
class ModelContext extends CommonContextFunctions implements Context, SnippetAcceptingContext
{
    private $familyContext;
    private $lineContext;
    private $sexContext;
    protected $url;
    
    public function __construct()
    {
        $this->url = "http://".BDECOTEX_SERVER.BDECOTEX_MAIN_URL."/model";
        
        $this->familyContext = new FamilyContext;
        $this->lineContext = new LineContext;
        $this->sexContext = new SexContext;
    }
 
    /**
     * @Given que el sistema contiene los sexos:
     */
    public function queElSistemaContieneLosSexos(TableNode $table)
    {
        $this->queLaTablaEstaVacia("sex");
        $hash = $table->getHash();
        foreach ($hash as $row) {
            $this->sexContext->elUsuarioCreaElSexoConCodigo($row['SEXO'], $row['COD']);
        }
    }

    /**
     * @Given que el sistema contiene las lineas:
     */
    public function queElSistemaContieneLasLineas(TableNode $table)
    {
        $this->queLaTablaEstaVacia("line");
        $hash = $table->getHash();
        foreach ($hash as $row) {
            $this->lineContext->elUsuarioCreaLaLineaConCodigo($row['LINEA'], $row['COD']);
        }
    }

    /**
     * @Given que el sistema contiene las familias:
     */
    public function queElSistemaContieneLasFamilias(TableNode $table)
    {
        $this->queLaTablaEstaVacia("family");
        $hash = $table->getHash();
        foreach ($hash as $row) {
            $this->familyContext->elUsuarioCreaLaFamiliaConCodigo($row['FAMILIA'], $row['COD']);
        }
    }

    /**
     * @When el usuario crea un modelo de la familia :arg1, linea :arg2, sexo :arg3 y variante :arg4
     */
    public function elUsuarioCreaUnModeloDeLaFamiliaLineaSexoYVariante($arg1, $arg2, $arg3, $arg4)
    {
        $model = $this->modelData2Array($arg1, $arg2, $arg3, $arg4);
        
        $method = UrlApi::URL_METHOD_POST;
        $url = $this->url;
        $modelData = ["xid_family"  => ($model['family']=="null" ? "" : $model['family']),
                      "xid_line"    => ($model['line']=="null" ? "" : $model['line']),
                      "xid_sex"     => ($model['sex']=="null" ? "" : $model['sex']),
                      "variant"     => ($model['variant']=="null" ? "" : $model['variant'])];
        $this->callUrl($method, $url, $modelData);
    }
    
    /**
     * @Given el usuario crea un modelo con los siguientes campos:
     */
    public function elUsuarioCreaUnModeloConLosSiguientesCampos(TableNode $table)
    {
        $modelData = $this->tableData2ModelArray($table);
        
        $method = UrlApi::URL_METHOD_POST;
        $url = $this->url;
        $this->callUrl($method, $url, $modelData);
    }
    
    /**
     * @When el usuario modifica el modelo previamente creado a familia :arg1, linea :arg2, sexo :arg3 y variante :arg4
     */
    public function elUsuarioModificaElModeloPreviamenteCreadoAFamiliaLineaSexoYVariante($arg1, $arg2, $arg3, $arg4)
    {
        $modeloPreviamenteCreado = $this->responseJson;
        $model = $this->modelData2Array($arg1, $arg2, $arg3, $arg4);
        
        $method = UrlApi::URL_METHOD_PUT;
        $url = $this->url . "/" . $modeloPreviamenteCreado->id_model;
        $modelData = ["xid_family"  => ($model['family']=="null" ? "" : $model['family']),
                      "xid_line"    => ($model['line']=="null" ? "" : $model['line']),
                      "xid_sex"     => ($model['sex']=="null" ? "" : $model['sex']),
                      "variant"     => ($model['variant']=="null" ? "" : $model['variant'])];
        $this->callUrl($method, $url, $modelData);
    }

    /**
     * @When el usuario modifica los siguientes campos:
     */
    public function elUsuarioModificaLosSiguientesCampos(TableNode $table)
    {
        $modeloPreviamenteCreado = $this->responseJson;
        
        $modelData = $this->tableData2ModelArray($table);
        
        $method = UrlApi::URL_METHOD_PUT;
        $url = $this->url . "/" . $modeloPreviamenteCreado->id_model;
        $this->callUrl($method, $url, $modelData);
    }
    
    /**
     * @When el usuario elimina el modelo creado
     */
    public function elUsuarioEliminaElModeloCreado()
    {
        $modeloPreviamenteCreado = $this->responseJson;
        $method = UrlApi::URL_METHOD_DELETE;
        $url = $this->url . "/" . $modeloPreviamenteCreado->id_model;
        $this->callUrl($method, $url);
    }
    
    /**
     * @When el usuario solicita el modelo identificandolo por el id
     */
    public function elUsuarioSolicitaElModeloIdentificandoloPorElId()
    {
        $modeloPreviamenteCreado = $this->responseJson;
        $method = UrlApi::URL_METHOD_GET;
        $url = $this->url . "/" . $modeloPreviamenteCreado->id_model;
        $this->callUrl($method, $url);
    }
    
    /**
     * @Given que en el sistema existen los modelos:
     */
    public function queEnElSistemaExistenLosModelos(TableNode $table)
    {
        $hash = $table->getHash();
        foreach ($hash as $row){
            $model = $this->modelData2Array($row['FAMILIA'], $row['LINEA'], $row['SEXO'], $row['VAR']);
        
            $method = UrlApi::URL_METHOD_POST;
            $url = $this->url;
            $modelData = ["xid_family"  => ($model['family']=="null" ? "" : $model['family']),
                          "xid_line"    => ($model['line']=="null" ? "" : $model['line']),
                          "xid_sex"     => ($model['sex']=="null" ? "" : $model['sex']),
                          "variant"     => ($model['variant']=="null" ? "" : $model['variant']),
                          "description" => ($row['DESCRIPCION']=="null" ? "" : $row['DESCRIPCION'])];
            $this->callUrl($method, $url, $modelData);
        }
    }

    /**
     * @When el usuario solicita el listado de todos los modelos
     */
    public function elUsuarioSolicitaElListadoDeTodosLosModelos()
    {
        $method = UrlApi::URL_METHOD_GET;
        $url = $this->url;
        $this->callUrl($method, $url);
    }
    
    public function findModelIntoJsonResponse($arg1, $arg2, $arg3, $arg4) {
        foreach ($this->responseJson as $model) {
            if ($model->xid_family == $arg1 && $model->xid_line == $arg2 && $model->xid_sex == $arg3 && $model->variant == $arg4){
                return $model->id_model;
            }
        }
        return FALSE;
    }
    
    private function modelData2Array($familyName, $lineName, $sexName, $variant) {
        $model = array();
        if ($familyName == "null"){
            $model['family'] = $familyName;
        } else {
            $this->familyContext->elUsuarioSolicitaElListadoDeTodasLasFamilias();
            $model['family'] = $this->familyContext->findFamilyIntoJsonResponse($familyName);
        }
        
        if ($lineName == "null"){
            $model['line'] = $lineName;
        } else {
            $this->lineContext->elUsuarioSolicitaElListadoDeTodasLasLineas();
            $model['line'] = $this->lineContext->findLineIntoJsonResponse($lineName);
        }
        
        if ($sexName == "null"){
            $model['sex'] = $sexName;
        } else {
            $this->sexContext->elUsuarioSolicitaElListadoDeTodosLosSexos();
            $model['sex'] = $this->sexContext->findSexIntoJsonResponse($sexName);
        }
        
        $model['variant'] = $variant;
        
        if( ! ($model['family'] && $model['line'] && $model['sex']) ){
            throw new Exception("Error at Cucumber Feature Definition. One of provided data (family=".$model['family'].", line=".$model['line']." or sex=".$model['sex'].") is not valid because was not previously created at the system.");
        }
        
        return $model;
    }
    
    private function tableData2ModelArray(TableNode $table) {
        $modelData = array();
        
        $hash = $table->getHash();
        foreach ($hash as $row) {
            if ($row['ATRIBUTO'] == "FAMILY") {
                $this->familyContext->elUsuarioSolicitaElListadoDeTodasLasFamilias();
                $modelData['xid_family'] = $this->familyContext->findFamilyIntoJsonResponse($row['VALOR']);
                if( ! $modelData['xid_family'] ){
                    throw new Exception("Error at Cucumber Feature Definition. Provided data family=".$row['VALOR']." is not valid because was not previously created at the system.");
                }
            } else if ($row['ATRIBUTO'] == "LINE") {
                $this->lineContext->elUsuarioSolicitaElListadoDeTodasLasLineas();
                $modelData['xid_line'] = $this->lineContext->findLineIntoJsonResponse($row['VALOR']);
                if( ! $modelData['xid_line'] ){
                    throw new Exception("Error at Cucumber Feature Definition. Provided data line=".$row['VALOR']." is not valid because was not previously created at the system.");
                }
            } else if ($row['ATRIBUTO'] == "SEX") {
                $this->sexContext->elUsuarioSolicitaElListadoDeTodosLosSexos();
                $modelData['xid_sex'] = $this->sexContext->findSexIntoJsonResponse($row['VALOR']);
                if( ! $modelData['xid_sex'] ){
                    throw new Exception("Error at Cucumber Feature Definition. Provided data sex=".$row['VALOR']." is not valid because was not previously created at the system.");
                }
            } else {
                $modelData[$row['ATRIBUTO']] = ($row['VALOR']=="null" ? "" : $row['VALOR']);
            }
        }
        
        return $modelData;
    }
}