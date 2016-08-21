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
     * @When el usuario crea el sexo :arg1 con codigo :arg2
     */
    public function elUsuarioCreaElSexoConCodigo($arg1, $arg2)
    {
        $method = UrlApi::URL_METHOD_POST;
        $url = "http://localhost/bdecotex/sex";
        $sexData = ["name"  => ("null" == $arg1 ? "" : $arg1),
                    "code"         => ("null" == $arg2 ? "" : $arg2)];
        $this->callUrl($method, $url, $sexData);
    }

}