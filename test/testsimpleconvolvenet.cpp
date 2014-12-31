//#include "OpenCLHelper.h"
//#include "ClConvolve.h"

#include <iostream>

#include "Timer.h"
#include "NeuralNet.h"
#include "AccuracyHelper.h"
#include "test/myasserts.h"

using namespace std;

void test1() {
    Timer timer;
    float *data = new float[2];
    data[0] = 0.5;
    data[1] = -0.5;
    int *labels = new int[2];
    labels[0] = 0;
    labels[1] = 1;
    float *expectedResults = new float[4];
    expectedResults[0] = 0.5;
    expectedResults[1] = -0.5;
    expectedResults[2] = -0.5;
    expectedResults[3] = 0.5;
    NeuralNet *net = NeuralNet::maker()->planes(1)->boardSize(1)->instance();
    net->convolutionalMaker()->numFilters(2)->filterSize(1)->biased()->insert();
    float weights1[] = {0.382147, -1.77522};
    float biasweights1[] = {-1.00181, 0.891056};
    net->initWeights(1, weights1);
    net->initBiasWeights(1, biasweights1);
    for( int epoch = 0; epoch < 30; epoch++ ) {
        net->epochMaker()
            ->learningRate(1)
            ->batchSize(2)
            ->numExamples(2)
            ->inputData(data)
            ->expectedOutputs(expectedResults)
            ->run();
//        net->printWeightsAsCode();
//        net->printBiasWeightsAsCode();
        cout << "loss, E, " << net->calcLoss(expectedResults) << endl;
//        net->print();
        float const*results = net->getResults();
        AccuracyHelper::printAccuracy( 2, 2, labels, results );
    }
//    net->print();

    float loss = net->calcLoss(expectedResults);
    cout << "loss, E, " << loss << endl;
    float const*results = net->getResults();
    AccuracyHelper::printAccuracy( 2, 2, labels, results );

    int numCorrect = AccuracyHelper::calcNumRight( 2, 2, labels, net->getResults() );
    cout << "accuracy: " << numCorrect << "/" << 2 << endl;
    assertEquals( numCorrect, 2 );
    assertLessThan( 0.01, loss );

    delete net;
}

void test2() {
    Timer timer;
    float data[] = { 0.5, 0.5, 0.5,
                    -0.5, 0.5, 0.5,
                    0.5, 0.5, 0.5,
    
                   0.5, 0.5, 0.5,
                   0.5, -0.5, 0.5,
                   0.5, 0.5, 0.5,

                    -0.5, -0.5, -0.5,
                    -0.5, 0.5, -0.5,
                    -0.5, -0.5, -0.5,
    
                   -0.5, -0.5, -0.5,
                   0.5, -0.5, -0.5,
                   -0.5, -0.5, -0.5
 };

    int *labels = new int[4];
    labels[0] = 0;
    labels[1] = 1;
    labels[2] = 0;
    labels[3] = 1;
    float *expectedResults = new float[8];
    expectedResults[0] = 0.5;
    expectedResults[1] = -0.5;
    expectedResults[2] = -0.5;
    expectedResults[3] = 0.5;
    expectedResults[4] = 0.5;
    expectedResults[5] = -0.5;
    expectedResults[6] = -0.5;
    expectedResults[7] = 0.5;
    NeuralNet *net = NeuralNet::maker()->planes(1)->boardSize(3)->instance();
    net->convolutionalMaker()->numFilters(2)->filterSize(3)->biased()->insert();
    float weights1[] = {-0.171115, 0.28369, 0.201354, -0.496124, 0.391512, 0.120458, 0.396952, -0.1356, -0.319595, 0.251043, 0.318859, 0.220892, -0.480651, -0.51708, 0.2173, 0.365935, 0.304687, -0.712624};
    float biasWeights1[] = {0.375101, 0.00130748};
    net->initWeights(1, weights1);
    net->initBiasWeights(1, biasWeights1 );
    float const*results = 0;
    for( int epoch = 0; epoch < 15; epoch++ ) {
        net->epochMaker()
            ->learningRate(1)
            ->batchSize(4)
            ->numExamples(4)
            ->inputData(data)
            ->expectedOutputs(expectedResults)
            ->run();
//        net->printWeightsAsCode();
//        net->printBiasWeightsAsCode();
        cout << "loss, E, " << net->calcLoss(expectedResults) << endl;
        results = net->getResults();
        AccuracyHelper::printAccuracy( 4, 2, labels, results );
    }
    net->print();
    float loss = net->calcLoss(expectedResults);
    cout << "loss, E, " << loss << endl;
    AccuracyHelper::printAccuracy( 4, 2, labels, results );
    int numCorrect = AccuracyHelper::calcNumRight( 4, 2, labels, net->getResults() );
    cout << "accuracy: " << numCorrect << "/" << 4 << endl;
    assertEquals( numCorrect, 4 );
    assertLessThan( 0.0001, loss );

    delete net;
}

void test3_relu() {
    Timer timer;
    float *data = new float[2];
    data[0] = 0.5;
    data[1] = -0.5;
    int *labels = new int[2];
    labels[0] = 0;
    labels[1] = 1;
    float *expectedResults = new float[4];
    expectedResults[0] = 1;
    expectedResults[1] = 0;
    expectedResults[2] = 0;
    expectedResults[3] = 1;
    NeuralNet *net = NeuralNet::maker()->planes(1)->boardSize(1)->instance();
    net->convolutionalMaker()->numFilters(2)->filterSize(1)->biased()->relu()->insert();
    float weights1[] = {-0.380177, -1.5738};
    float biasWeights1[] = {0.5, 0.0606055};
    net->initWeights( 1, weights1, biasWeights1 );
    for( int epoch = 0; epoch < 15; epoch++ ) {
        net->epochMaker()
            ->learningRate(1)
            ->batchSize(2)
            ->numExamples(2)
            ->inputData(data)
            ->expectedOutputs(expectedResults)
            ->run();
        cout << "loss, E, " << net->calcLoss(expectedResults) << endl;
//        net->print();
//        net->printWeightsAsCode();
//        net->printBiasWeightsAsCode();
        float const*results = net->getResults();
        AccuracyHelper::printAccuracy( 2, 2, labels, results );
    }
    net->print();
    float loss = net->calcLoss(expectedResults);
    cout << "loss, E, " << loss << endl;
    float const*results = net->getResults();
    AccuracyHelper::printAccuracy( 2, 2, labels, results );

    int numCorrect = AccuracyHelper::calcNumRight( 2, 2, labels, net->getResults() );
    cout << "accuracy: " << numCorrect << "/" << 2 << endl;
    assertEquals( numCorrect, 2 );

    assertLessThan( 0.001, loss );

    delete net;
}

void test4_relu() {
    Timer timer;
    float data[] = { 0.5, 0.5, 0.5,
                    -0.5, 0.5, 0.5,
                    0.5, 0.5, 0.5,
    
                   0.5, 0.5, 0.5,
                   0.5, -0.5, 0.5,
                   0.5, 0.5, 0.5,

                    -0.5, -0.5, -0.5,
                    -0.5, 0.5, -0.5,
                    -0.5, -0.5, -0.5,
    
                   -0.5, -0.5, -0.5,
                   0.5, -0.5, -0.5,
                   -0.5, -0.5, -0.5
 };

    int *labels = new int[4];
    labels[0] = 0;
    labels[1] = 1;
    labels[2] = 0;
    labels[3] = 1;
    float *expectedResults = new float[8];
    expectedResults[0] = 1;
    expectedResults[1] = 0;
    expectedResults[2] = 0;
    expectedResults[3] = 1;
    expectedResults[4] = 1;
    expectedResults[5] = 0;
    expectedResults[6] = 0;
    expectedResults[7] = 1;
    NeuralNet *net = NeuralNet::maker()->planes(1)->boardSize(3)->instance();
    net->convolutionalMaker()->numFilters(2)->filterSize(3)->biased()->relu()->insert();
    float const*results = 0;
    for( int epoch = 0; epoch < 20; epoch++ ) {
        net->epochMaker()
            ->learningRate(1)
            ->batchSize(4)
            ->numExamples(4)
            ->inputData(data)
            ->expectedOutputs(expectedResults)
            ->run();
        results = net->getResults();
        AccuracyHelper::printAccuracy( 4, 2, labels, results );
    }
    net->print();
    cout << "loss, E, " << net->calcLoss(expectedResults) << endl;
    AccuracyHelper::printAccuracy( 4, 2, labels, results );
    int numCorrect = AccuracyHelper::calcNumRight( 4, 2, labels, net->getResults() );
    cout << "accuracy: " << numCorrect << "/" << 4 << endl;
    assertEquals( numCorrect, 4 );

    delete net;
}

void test5_linear() {
    Timer timer;
    float data[] = { 0.5, 0.5, 0.5,
                    -0.5, 0.5, 0.5,
                    0.5, 0.5, 0.5,
    
                   0.5, 0.5, 0.5,
                   0.5, -0.5, 0.5,
                   0.5, 0.5, 0.5,

                    -0.5, -0.5, -0.5,
                    -0.5, 0.5, -0.5,
                    -0.5, -0.5, -0.5,
    
                   -0.5, -0.5, -0.5,
                   0.5, -0.5, -0.5,
                   -0.5, -0.5, -0.5
 };

    int *labels = new int[4];
    labels[0] = 0;
    labels[1] = 1;
    labels[2] = 0;
    labels[3] = 1;
    float *expectedResults = new float[8];
    expectedResults[0] = 1;
    expectedResults[1] = 0;
    expectedResults[2] = 0;
    expectedResults[3] = 1;
    expectedResults[4] = 1;
    expectedResults[5] = 0;
    expectedResults[6] = 0;
    expectedResults[7] = 1;
    NeuralNet *net = NeuralNet::maker()->planes(1)->boardSize(3)->instance();
    net->convolutionalMaker()->numFilters(2)->filterSize(3)->biased()->linear()->insert();
    float const*results = 0;
    for( int epoch = 0; epoch < 20; epoch++ ) {
        net->epochMaker()
            ->learningRate(1)
            ->batchSize(4)
            ->numExamples(4)
            ->inputData(data)
            ->expectedOutputs(expectedResults)
            ->run();
        results = net->getResults();
        AccuracyHelper::printAccuracy( 4, 2, labels, results );
    }
    net->print();
    cout << "loss, E, " << net->calcLoss(expectedResults) << endl;
    AccuracyHelper::printAccuracy( 4, 2, labels, results );
    int numCorrect = AccuracyHelper::calcNumRight( 4, 2, labels, net->getResults() );
    cout << "accuracy: " << numCorrect << "/" << 4 << endl;
    assertEquals( numCorrect, 4 );

    delete net;
}

void test6_point_2layer() {
    Timer timer;
    float *data = new float[2];
    data[0] = 0.5;
    data[1] = -0.5;
    int *labels = new int[2];
    labels[0] = 0;
    labels[1] = 1;
    float *expectedResults = new float[4];
    expectedResults[0] = 0.5;
    expectedResults[1] = -0.5;
    expectedResults[2] = -0.5;
    expectedResults[3] = 0.5;
    NeuralNet *net = NeuralNet::maker()->planes(1)->boardSize(1)->instance();
    net->convolutionalMaker()->numFilters(2)->filterSize(1)->biased(0)->insert();
    net->convolutionalMaker()->numFilters(2)->filterSize(1)->biased(0)->insert();
    for( int epoch = 0; epoch < 100; epoch++ ) {
        net->epochMaker()
            ->learningRate(1)
            ->batchSize(2)
            ->numExamples(2)
            ->inputData(data)
            ->expectedOutputs(expectedResults)
            ->run();
//        cout << "loss, E, " << net->calcLoss(expectedResults) << endl;
//        net->print();
        float const*results = net->getResults();
//        AccuracyHelper::printAccuracy( 2, 2, labels, results );
    }
    net->print();
    cout << "loss, E, " << net->calcLoss(expectedResults) << endl;
    float const*results = net->getResults();
    AccuracyHelper::printAccuracy( 2, 2, labels, results );

    int numCorrect = AccuracyHelper::calcNumRight( 2, 2, labels, net->getResults() );
    cout << "accuracy: " << numCorrect << "/" << 2 << endl;
    assertEquals( numCorrect, 2 );

    delete net;
}

int main( int argc, char *argv[] ) {
    int testNum = -1;
    int numIts = 10;
    if( argc >= 2 ) {
        testNum = atoi( argv[1] );
        numIts = 1;
    }
    if( argc >= 3  ){
        numIts = atoi(argv[2] );
    }

    if( testNum == -1 ) {
        test1();
        test2();
        test3_relu();
    }

    for( int it = 0; it < numIts; it++ ) {
//            test4_relu();
        if( testNum == 1 ) test1();
        if( testNum == 2 ) test2();
        if( testNum == 3 ) test3_relu();
        if( testNum == 4 ) test4_relu();
        if( testNum == 5 ) test5_linear();
        if( testNum == 6 ) test6_point_2layer();
    }

    return 0;
}


