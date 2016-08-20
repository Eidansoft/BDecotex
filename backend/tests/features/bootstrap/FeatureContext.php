<?php
require_once (dirname(__FILE__).'/../../httpCallsAPI.php');
require_once (dirname(__FILE__).'/../../phpunit-5.5.0.phar');
require_once (dirname(__FILE__).'/../../../app/model/BDecotexDAOImpl.php.inc');

use Behat\Behat\Tester\Exception\PendingException;
use Behat\Behat\Context\Context;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;

/**
 * Defines application features from the specific context.
 */
class FeatureContext implements Context, SnippetAcceptingContext
{
    private $responseJson;
    private $responseCode;

    /**
     * Initializes context.
     *
     * Every scenario gets its own context instance.
     * You can also pass arbitrary arguments to the
     * context constructor through behat.yml.
     */
    public function __construct()
    {
    }
    
    /**
     * @Given que la tabla :arg1 esta vacia
     */
    public function queLaTablaEstaVacia($arg1)
    {
        $dao = new BDecotexDAOImpl($arg1);
        $dao->deleteAll();
    }

    /**
     * @When el usuario crea la familia :arg1 con codigo :arg2
     */
    public function elUsuarioCreaLaFamiliaConCodigo($arg1, $arg2)
    {
        $method = UrlApi::URL_METHOD_POST;
        $url = "http://localhost/bdecotex/family";
        $familyData = ["description"  => ("null" == $arg1 ? "" : $arg1),
                             "code"         => ("null" == $arg2 ? "" : $arg2)];
        $this->callUrl($method, $url, $familyData);
    }

    /**
     * @Then el sistema devuelve un codigo http :arg1
     */
    public function elSistemaDevuelveUnCodigoHttp($arg1)
    {
        PHPUnit_Framework_Assert::assertSame(
            intval($arg1),
            $this->responseCode,
            "The system returned HTTP code " . $this->responseCode . ", instead $arg1"
        );
    }

    /**
     * @When el usuario modifica la familia al nuevo nombre :arg1 con codigo :arg2
     */
    public function elUsuarioModificaLaFamiliaAlNuevoNombreConCodigo($arg1, $arg2)
    {
        $familiaPreviamenteCreada = $this->responseJson;
        $method = UrlApi::URL_METHOD_PUT;
        $url = "http://localhost/bdecotex/family/" . $familiaPreviamenteCreada->id_family;
        $familyData = ["description"  => ("null" == $arg1 ? "" : $arg1),
                       "code"         => ("null" == $arg2 ? "" : $arg2)];
        $this->callUrl($method, $url, $familyData);
    }

    /**
     * @When el usuario elimina la familia creada
     */
    public function elUsuarioEliminaLaFamiliaCreada()
    {
        $familiaPreviamenteCreada = $this->responseJson;
        $method = UrlApi::URL_METHOD_DELETE;
        $url = "http://localhost/bdecotex/family/" . $familiaPreviamenteCreada->id_family;
        $this->callUrl($method, $url);
    }
    
    /**
     * @Then el sistema incluye en la respuesta los siguientes atributos:
     */
    public function elSistemaIncluyeEnLaRespuestaLosSiguientesAtributos(TableNode $table)
    {
        $hash = $table->getHash();
        foreach ($hash as $row) {
            if ( ! array_key_exists($row['ATRIBUTO'], $this->responseJson)){
                throw new Exception("Missing mandatory atribute '" . $row['ATRIBUTO'] . "'");
            }
            if (array_key_exists("VALOR", $row) && $row['VALOR'] != ""){
                if (1 == preg_match("/^regex\((.+)\)$/", $row['VALOR'], $coincidencias)){
                    PHPUnit_Framework_Assert::assertStringMatchesFormat(
                    $coincidencias[1],
                    $this->responseJson->id_family,
                    "Expected value for '" . $row['ATRIBUTO'] . "' attribute was the regex expression '" . $coincidencias[1] . "', but the value '" . $this->responseJson->$row['ATRIBUTO'] . "' found at the response did not match the expression"
                );
                } else {
                    PHPUnit_Framework_Assert::assertSame(
                        $row['VALOR'],
                        $this->responseJson->$row['ATRIBUTO'],
                        "Expected value for '" . $row['ATRIBUTO'] . "' attribute was '" . $row['VALOR'] . "', but '" . $this->responseJson->$row['ATRIBUTO'] . "' was found"
                    );
                }
            }
        }
    }
    
    /**
     * @Given que en el sistema existen las familias:
     */
    public function queEnElSistemaExistenLasFamilias(TableNode $table)
    {
        $hash = $table->getHash();
        foreach ($hash as $row) {
            $this->elUsuarioCreaLaFamiliaConCodigo($row['NOMBRE'], $row['CODIGO']);
        }
    }

    /**
     * @When el usuario solicita el listado de todas las familias
     */
    public function elUsuarioSolicitaElListadoDeTodasLasFamilias()
    {
        $method = UrlApi::URL_METHOD_GET;
        $url = "http://localhost/bdecotex/family";
        $this->callUrl($method, $url);
    }

    /**
     * @Then el sistema incluye el listado con las familias:
     */
    public function elSistemaIncluyeElListadoConLasFamilias(TableNode $table)
    {
        $hash = $table->getHash();
        foreach ($hash as $row) {
            if ( ! $this->findFamilyIntoJsonResponse($row['NOMBRE'], $row['CODIGO']) ){
                throw new Exception("Expected family '" . $row['NOMBRE'] . "' with code '" . $row['CODIGO'] . "' not found at server response");
            }
        }
    }

    private function callUrl($method, $url, $params = null) {
        if (null == $params){
            $conection = new UrlApi($url, $method);
        } else {
            $conection = new UrlApi($url, $method, json_encode($params));
        }
        $conection->call();
        $this->responseCode = $conection->getHttpCode();
        $this->responseJson = json_decode($conection->getResponse());
    }
    
    private function findFamilyIntoJsonResponse($name, $code) {
        foreach ($this->responseJson as $family) {
            if ($family->description == $name && $family->code == $code){
                return TRUE;
            }
        }
        return FALSE;
    }
}
