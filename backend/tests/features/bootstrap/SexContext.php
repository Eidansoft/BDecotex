<?php
require_once (dirname(__FILE__).'/CommonContextFunctions.php');
require_once (dirname(__FILE__).'/../../httpCallsAPI.php');

use Behat\Behat\Tester\Exception\PendingException;
use Behat\Behat\Context\Context;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;

/**
 * Defines application features from the Sex context.
 */
class SexContext extends CommonContextFunctions implements Context, SnippetAcceptingContext
{
    protected $url;
    
    public function __construct()
    {
        $this->url = "http://".BDECOTEX_SERVER.BDECOTEX_MAIN_URL."/sex";
    }
    
    /**
     * @When el usuario crea el sexo :arg1 con codigo :arg2
     */
    public function elUsuarioCreaElSexoConCodigo($arg1, $arg2)
    {
        $method = UrlApi::URL_METHOD_POST;
        $url = $this->url;
        $sexData = ["name"  => ("null" == $arg1 ? "" : $arg1),
                    "code"         => ("null" == $arg2 ? "" : $arg2)];
        $this->callUrl($method, $url, $sexData);
    }

    /**
     * @When el usuario modifica el sexo al nuevo nombre :arg1 con codigo :arg2
     */
    public function elUsuarioModificaElSexoAlNuevoNombreConCodigo($arg1, $arg2)
    {
        $sexoPreviamenteCreado = $this->responseJson;
        $method = UrlApi::URL_METHOD_PUT;
        $url = $this->url . "/" . $sexoPreviamenteCreado->id_sex;
        $sexData = ["name"  => ("null" == $arg1 ? "" : $arg1),
                    "code"  => ("null" == $arg2 ? "" : $arg2)];
        $this->callUrl($method, $url, $sexData);
    }
    /**
     * @Given que en el sistema existen los sexos:
     */
    public function queEnElSistemaExistenLosSexos(TableNode $table)
    {
        $hash = $table->getHash();
        foreach ($hash as $row) {
            $this->elUsuarioCreaElSexoConCodigo($row['NOMBRE'], $row['CODIGO']);
        }
    }

    /**
     * @When el usuario solicita el listado de todos los sexos
     */
    public function elUsuarioSolicitaElListadoDeTodosLosSexos()
    {
        $method = UrlApi::URL_METHOD_GET;
        $url = $this->url;
        $this->callUrl($method, $url);
    }

    /**
     * @Then el sistema incluye el listado con los sexos:
     */
    public function elSistemaIncluyeElListadoConLosSexos(TableNode $table)
    {
        $hash = $table->getHash();
        foreach ($hash as $row) {
            if ( ! $this->findSexIntoJsonResponse($row['NOMBRE'], $row['CODIGO']) ){
                throw new Exception("Expected sex '" . $row['NOMBRE'] . "' with code '" . $row['CODIGO'] . "' not found at server response");
            }
        }
    }
    
    /**
     * @When el usuario elimina el sexo creado
     */
    public function elUsuarioEliminaElSexoCreado()
    {
        $sexoPreviamenteCreado = $this->responseJson;
        $method = UrlApi::URL_METHOD_DELETE;
        $url = $this->url . "/" . $sexoPreviamenteCreado->id_sex;
        $this->callUrl($method, $url);
    }
    
    public function findSexIntoJsonResponse($name, $code = null) {
        foreach ($this->responseJson as $sex) {
            if ($sex->name == $name){
                if ($code == null || $sex->code == $code){
                    return $sex->id_sex;
                }
            }
        }
        return FALSE;
    }
}