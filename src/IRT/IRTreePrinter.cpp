//
// Created by gregory on 24.12.18.
//

#include <iostream>
#include <fstream>
#include "IRTreePrinter.h"

#include "IIRVisitor.h"

using namespace std;

namespace IRTree {

    void IRTreePrinter::Visit( const CMove* node )
    {
        node->GetDestExpr()->Accept( this );
        string destString = lastNodeName;

        node->GetSrcExpr()->Accept( this );
        string srcString = lastNodeName;

        nextNameWithId( "move" );

        AddEdge( lastNodeName, destString, "dest" );
        AddEdge( lastNodeName, srcString, "src" );
    }

    void IRTreePrinter::Visit( const CExpr* node )
    {
        node->GetExp()->Accept( this );
        string prevString = lastNodeName;

        nextNameWithId( "exp" );
        AddEdge( lastNodeName, prevString );
    }

    void IRTreePrinter::Visit( const CJump* node )
    {
        nextNameWithId( "jump" );
        for( auto label : node->GetLabels() ) {
            AddEdge( lastNodeName, label->GetName()->GetString(), "to_label" );
        }
    }

    void IRTreePrinter::Visit( const CCondJump* node )
    {
        node->GetRightExpr()->Accept( this );
        string rightString = lastNodeName;
        node->GetLeftExpr()->Accept( this );
        string leftString = lastNodeName;

        nextNameWithId( "CondJump" );

        AddEdge( lastNodeName, leftString, "left" );
        AddEdge( lastNodeName, "binop_Eq", "binop_Eq" );
        AddEdge( lastNodeName, rightString, "right" );
        AddEdge( lastNodeName, node->GetIfTrueLabel()->GetName()->GetString(), "iftrue" );
        AddEdge( lastNodeName, node->GetIfFalseLabel()->GetName()->GetString(), "iffalse" );
    }

    void IRTreePrinter::Visit( const CSeq* node )
    {
        if( node->GetLeftStm() != nullptr ) {
            node->GetLeftStm()->Accept( this );
            string leftString = lastNodeName;
            if( node->GetRightStm() != nullptr ) {
                node->GetRightStm()->Accept( this );
                string rightString = lastNodeName;
                nextNameWithId( "seq" );
                AddEdge( lastNodeName, leftString, "left" );
                AddEdge( lastNodeName, rightString, "right" );
            } else {
                nextNameWithId( "seq" );
                AddEdge( lastNodeName, leftString, "left" );
            }
        } else {
            nextNameWithId( "seq" );
        }
    }

    void IRTreePrinter::Visit( const CConst* node )
    {
        nextNameWithId( string( "const_" ) + to_string( node->GetValue() ) );
    }

    void IRTreePrinter::Visit( const CName* node )
    {
        nextNameWithId( string( "name_" ) + node->GetName()->GetName()->GetString() );
    }

    void IRTreePrinter::Visit( const CTemp* node )
    {
        nextNameWithId( string( "temp_" ) + node->GetTemp()->GetName()->GetString() );
    }

    void IRTreePrinter::Visit( const CBinop* node )
    {
        node->GetLeft()->Accept( this );
        string leftString = lastNodeName;
        node->GetRight()->Accept( this );
        string rightString = lastNodeName;
        switch( node->GetBinOp() ) {
            case IRTree::IExpr::MUL:
                nextNameWithId( "binop__Mul" );
                break;
            case IRTree::IExpr::PLUS:
                nextNameWithId( "binop__Plus" );
                break;
            case IRTree::IExpr::DIV:
                nextNameWithId( "binop__Division" );
                break;
            case IRTree::IExpr::MINUS:
                nextNameWithId( "binop__Minus" );
                break;
            case IRTree::IExpr::XOR:
                nextNameWithId( "binop__Xor" );
                break;
            case IRTree::IExpr::LESS:
                nextNameWithId( "binop__Less" );
                break;
            case IRTree::IExpr::GT:
                nextNameWithId( "binop__Greater" );
                break;
            case IRTree::IExpr::AND:
                nextNameWithId( "binop__And" );
                break;
        }
        AddEdge( lastNodeName, rightString, "right" );
        AddEdge( lastNodeName, leftString, "left" );
    }

    void IRTreePrinter::Visit( const CMem* node )
    {
        node->GetMem()->Accept( this );
        string prevString = lastNodeName;
        nextNameWithId( "mem" );
        AddEdge( lastNodeName, prevString );
    }

    void IRTreePrinter::Visit( const CCall* node )
    {
        string funcString = node->GetFunctionName();
        //string argsString;
        std::vector<string> nodes;
        for(const auto &arg : node->GetArguments() ) {
            arg->Accept( this );
            nodes.push_back( lastNodeName );
        }
        nextNameWithId( "call" );
        AddEdge( lastNodeName, funcString, "func" );
        for (const auto &node : nodes) {
            AddEdge( lastNodeName, node, "arg" );
        }

    }

    void IRTreePrinter::Visit( const CESeq* node )
    {
        node->GetStatement()->Accept( this );
        string stmString = lastNodeName;
        node->GetExpression()->Accept( this );
        string expString = lastNodeName;
        nextNameWithId( "eseq" );
        AddEdge( lastNodeName, expString, "exp" );
        AddEdge( lastNodeName, stmString, "stm" );
    }

    void IRTreePrinter::Visit( const CLabel* node )
    {
        nextNameWithId( string( "label:" ) + node->GetLabel()->GetName()->GetString() );
    }

    void IRTreePrinter::nextNameWithId( std::string label )
    {
        lastNodeName = label + string( "__id_" ) + to_string( minId++ );
        SetNodeLabel( lastNodeName, label );
    }

    /*void IRTreePrinter::LinkedVisit( const IStm* node )
    {
        string fromName = lastNodeName;
        node->Accept( this );
        string toName = lastNodeName;
        if( !fromName.empty() ) {
            AddEdge( fromName, toName, "next" );
        }
    }

    void IRTreePrinter::LinkedVisit( const IExpr* node )
    {
        string fromName = lastNodeName;
        node->Accept( this );
        string toName = lastNodeName;
        if( !fromName.empty() ) {
            AddEdge( fromName, toName, "next" );
        }
    }*/

    void IRTreePrinter::AddEdge( std::string from, std::string to )
    {

        decorateName( from );
        decorateName( to );
        data += from + " -> " + to + " ; \n";
    }

    void IRTreePrinter::AddEdge( std::string from, std::string to, std::string edgeName )
    {

        decorateName( from );
        decorateName( to );
        decorateName( edgeName );
        data += from + " -> " + to + " [ label=\"" + edgeName + "\"] ; \n";
    }

    void IRTreePrinter::Flush()
    {
        data += "\n}";
        std::ofstream out ( filename );
        out << data;
        out.close();
        isFlushed = true;
    }

    void IRTreePrinter::SetNodeLabel( std::string nodeName, std::string nodeLabel )
    {

        data += nodeName + " [ label=\"" + nodeLabel + "\" ]; \n";
    }

    void IRTreePrinter::decorateName( std::string& stringToDecorate )
    {
        for( int i = 0; i < stringToDecorate.size(); i++ ) {
            if( stringToDecorate[i] == '.' || stringToDecorate[i] == ':' || stringToDecorate[i] == '=' ) {
                stringToDecorate[i] = '_';
            }
        }
    }
}