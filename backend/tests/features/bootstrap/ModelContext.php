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
    /**
     * Initializes context.
     *
     * Every scenario gets its own context instance.
     * You can also pass arbitrary arguments to the
     * context constructor through behat.yml.
     */
    public function __construct()
    {
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
        if ($arg1 == "null"){
            $family = $arg1;
        } else {
            $this->familyContext->elUsuarioSolicitaElListadoDeTodasLasFamilias();
            $family = $this->familyContext->findFamilyIntoJsonResponse($arg1);
        }
        
        if ($arg2 == "null"){
            $line = $arg2;
        } else {
            $this->lineContext->elUsuarioSolicitaElListadoDeTodasLasLineas();
            $line = $this->lineContext->findFamilyIntoJsonResponse($arg2);
        }
        
        if ($arg3 == "null"){
            $sex = $arg3;
        } else {
            $this->sexContext->elUsuarioSolicitaElListadoDeTodosLosSexos();
            $sex = $this->sexContext->findSexIntoJsonResponse($arg3);
        }
        
        $variante = $arg4;
        
        if($family && $line && $sex){
            $method = UrlApi::URL_METHOD_POST;
            $url = "http://localhost/bdecotex/mod";
            $modelData = ["family"  => ($family=="null" ? "" : $family),
                          "line"    => ($line=="null" ? "" : $line),
                          "sex"     => ($sex=="null" ? "" : $sex),
                          "variant" => ($variante=="null" ? "" : $variante)];
            $this->callUrl($method, $url, $modelData);
        } else {
            throw new Exception("Error at Cucumber Feature Definition. One of provided data (family=$family, line=$line or sex=$sex) is not valid because was not previously created at the system.");
        }
    }

    /**
     * @When el usuario modifica el campo :arg1 al valor :arg2
     */
    public function elUsuarioModificaElCampoAlValor($arg1, $arg2)
    {
        $modeloPreviamenteCreado = $this->responseJson;
        $value = $arg2;
        if ($arg1 == "xid_family"){
            $value = $this->familyContext->findFamilyIntoJsonResponse($arg2);
        } else if ($arg1 == "xid_line"){
            $value = $this->lineContext->findFamilyIntoJsonResponse($arg2);
        } else if ($arg1 == "xid_sex"){
            $value = $this->sexContext->findSexIntoJsonResponse($arg2);
        }
        
        $method = UrlApi::URL_METHOD_PUT;
        $url = "http://localhost/bdecotex/mod/" . $modeloPreviamenteCreado->id_model;
        $modelData = ["attribute"  => ($arg1=="null" ? "" : $arg1),
                      "value"      => ($arg2=="null" ? "" : $value)];
        $this->callUrl($method, $url, $modelData);
    }

    /**
     * @When el usuario elimina el modelo creado
     */
    public function elUsuarioEliminaElModeloCreado()
    {
        $modeloPreviamenteCreado = $this->responseJson;
        $method = UrlApi::URL_METHOD_DELETE;
        $url = "http://localhost/bdecotex/mod/" . $modeloPreviamenteCreado->id_model;
        $this->callUrl($method, $url);
    }
    
    /**
     * @When el usuario modifica los siguientes campos:
     */
    public function elUsuarioModificaLosSiguientesCampos(TableNode $table)
    {
        $hash = $table->getHash();
        foreach ($hash as $row) {
            $this->elUsuarioModificaElCampoAlValor($row['ATRIBUTO'], $row['VALOR']);
        }
    }
    
    /**
     * @When el usuario solicita el modelo identificandolo por el id
     */
    public function elUsuarioSolicitaElModeloIdentificandoloPorElId()
    {
        $modeloPreviamenteCreado = $this->responseJson;
        $method = UrlApi::URL_METHOD_GET;
        $url = "http://localhost/bdecotex/mod/" . $modeloPreviamenteCreado->id_model;
        $this->callUrl($method, $url);
    }
    
    /**
     * @Given que en el sistema existen los modelos:
     */
    public function queEnElSistemaExistenLosModelos(TableNode $table)
    {
        $hash = $table->getHash();
        foreach ($hash as $row){
            $this->elUsuarioCreaUnModeloDeLaFamiliaLineaSexoYVariante($row['FAMILIA'], $row['LINEA'], $row['SEXO'], $row['VAR']);
        }
    }

    /**
     * @When el usuario solicita el listado de todos los modelos
     */
    public function elUsuarioSolicitaElListadoDeTodosLosModelos()
    {
        $method = UrlApi::URL_METHOD_GET;
        $url = "http://localhost/bdecotex/mod";
        $this->callUrl($method, $url);
    }

    /**
     * @Then el sistema incluye el listado con los modelos:
     */
    public function elSistemaIncluyeElListadoConLosModelos(TableNode $table)
    {
        $allModelsResponse = $this->responseJson;
        $hash = $table->getHash();
        foreach ($hash as $row) {
            $this->familyContext->elUsuarioSolicitaElListadoDeTodasLasFamilias();
            $family = $this->familyContext->findFamilyIntoJsonResponse($row['FAMILIA']);
            
            $this->lineContext->elUsuarioSolicitaElListadoDeTodasLasLineas();
            $line = $this->lineContext->findFamilyIntoJsonResponse($row['LINEA']);
            
            $this->sexContext->elUsuarioSolicitaElListadoDeTodosLosSexos();
            $sex = $this->sexContext->findSexIntoJsonResponse($row['SEXO']);
            
            //I have made HTTP calls between the 'getAllModel' method and the result evaluation below
            //that's the reason I need to recover it here
            $this->responseJson = $allModelsResponse;
            if ( ! $this->findModelIntoJsonResponse($family, $line, $sex, $row['VAR'])){
                throw new Exception("Expected model with family '" . $row['FAMILIA'] . "' (id:$family), line '" . $row['LINEA'] . "'(id:$line), sex '" . $row['SEXO'] . "(id:$sex)' and variant '" . $row['VAR'] . "'; but missing at system response'");
            }
        }
    }
    
    public function findModelIntoJsonResponse($arg1, $arg2, $arg3, $arg4) {
        foreach ($this->responseJson as $model) {
            if ($model->xid_family == $arg1 && $model->xid_line == $arg2 && $model->xid_sex == $arg3 && $model->variant == $arg4){
                return $model->id_model;
            }
        }
        return FALSE;
    }
}