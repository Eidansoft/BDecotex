<?php
require_once (dirname(__FILE__).'/../../httpCallsAPI.php');
require_once (dirname(__FILE__).'/../../phpunit-5.5.0.phar');

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
    private $familyData;
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
     * @Given El servidor esta corriendo
     */
    public function elServidorEstaCorriendo()
    {
        // Metodo creado por claridad expresiva en los SAT
        //throw new PendingException();
    }

    /**
     * @When el usuario crea la familia :arg1 con codigo :arg2
     */
    public function elUsuarioCreaLaFamiliaConCodigo($arg1, $arg2)
    {
        $method = UrlApi::URL_METHOD_POST;
        $url = "http://localhost/bdecotex/family";
        $this->familyData = ["description"=>$arg1,"code"=>$arg2];
        $conection = new UrlApi($url, $method, json_encode($this->familyData));
        $conection->call();
        $this->responseCode = $conection->getHttpCode();
        $this->responseJson = json_decode($conection->getResponse());
    }

    /**
     * @Then el sistema responde un codigo http :arg1
     */
    public function elSistemaRespondeUnCodigoHttp($arg1)
    {
        PHPUnit_Framework_Assert::assertSame(
            intval($arg1),
            $this->responseCode,
            "The system returned HTTP code " . $this->responseCode . ", instead $arg1"
        );
    }

    /**
     * @Then el sistema responde con la familia enviada
     */
    public function elSistemaRespondeConLaFamiliaEnviada()
    {
        PHPUnit_Framework_Assert::assertStringMatchesFormat(
            "%d",
            $this->responseJson->id_family,
            "The family returned has no a valid ID"
        );
        
        PHPUnit_Framework_Assert::assertSame(
            $this->familyData["description"],
            $this->responseJson->description,
            "The family returned a wrong description"
        );
        
        PHPUnit_Framework_Assert::assertSame(
            $this->familyData['code'],
            $this->responseJson->code,
            "The family returned a wrong code"
        );
    }

    /**
     * @Given existe al menos una familia creada en el sistema
     */
    public function existeAlMenosUnaFamiliaCreadaEnElSistema()
    {
        elUsuarioCreaLaFamiliaConCodigo("Familia para editar", "002");
        $this->familyData = $this->responseJson;
    }

    /**
     * @When el usuario modifica la familia al nuevo nombre :arg1 con codigo :arg2
     */
    public function elUsuarioModificaLaFamiliaAlNuevoNombreConCodigo($arg1, $arg2)
    {
        throw new PendingException();
    }
}
