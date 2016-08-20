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
        $this->familyData = ["description"  => ("null" == $arg1 ? "" : $arg1),
                             "code"         => ("null" == $arg2 ? "" : $arg2)];
        $conection = new UrlApi($url, $method, json_encode($this->familyData));
        $conection->call();
        $this->responseCode = $conection->getHttpCode();
        $this->responseJson = json_decode($conection->getResponse());
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
        $this->familyData = ["description"  => ("null" == $arg1 ? "" : $arg1),
                             "code"         => ("null" == $arg2 ? "" : $arg2)];
        $conection = new UrlApi($url, $method, json_encode($this->familyData));
        $conection->call();
        $this->responseCode = $conection->getHttpCode();
        $this->responseJson = json_decode($conection->getResponse());
    }

}
