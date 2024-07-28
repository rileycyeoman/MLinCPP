#include "baseNN.hpp"
NeuralNetwork::NeuralNetwork(std::vector<uint> topology, Scalar learningRate = Scalar(0.005)){
    this->topology = topology;
    this->learningRate = learningRate;

    for (uint i = 0; i< topology.size(); i++){
        if (i == topology.size() - 1)
            neuronLayers.push_back(new RowVector(topology[i]));
        else
            neuronLayers.push_back(new RowVector(topology[i] + 1));
        
        cacheLayers.push_back(new RowVector(neuronLayers.size()));
        deltas.push_back(new RowVector(neuronLayers.size()));

        if (i != topology.size() - 1){
            neuronLayers.back()->coeffRef(topology[i]) = 1.0;
            cacheLayers.back()->coeffRef(topology[i]) = 1.0;
        }
        if (i > 0){
            
        }
    }
}

void NeuralNetwork::propagateForward(RowVector& input){

}

void NeuralNetwork:: propagateBackward(RowVector& output){

}

void NeuralNetwork::calcErrors(RowVector& output){

}

void NeuralNetwork::updateWeights(){

}

void NeuralNetwork::train(std::vector<RowVector*> data){

}