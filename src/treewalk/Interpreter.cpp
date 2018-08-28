#include <Interpreter.h>

#include <memory>

#include <ASTree.h>

void Interpreter::visit(AST::AssignStmt *node) {
    node->m_expr->accept(this);
    const DurianObject val = m_dataStack.top();
    m_dataStack.pop();
    m_currentScope->assign(node->m_ident->m_identStr, val);
}

void Interpreter::visit(AST::BinaryExpr *node) {
    node->m_left->accept(this);
    node->m_right->accept(this);
    const DurianObject right = m_dataStack.top();
    m_dataStack.pop();
    const DurianObject left = m_dataStack.top();
    m_dataStack.pop();
    switch (node->m_op) {
        case TokenType::And:
            if (left.isTruthy()) {
                if (right.isTruthy()) {
                    m_dataStack.push(DurianObject(true));
                    break;
                }
            }
            m_dataStack.push(DurianObject(false));
            break;
        case TokenType::Or:
            if (left.isTruthy()) {
                m_dataStack.push(DurianObject(true));
                break;
            }
            if (right.isTruthy()) {
                m_dataStack.push(DurianObject(true));
                break;
            }
            m_dataStack.push(DurianObject(false));
            break;
        case TokenType::Ampersand:
            // TODO
            break;
        case TokenType::Plus:
            if (left.type == DurianType::Integer) {
                if (right.type == DurianType::Integer) {
                    m_dataStack.push(DurianObject(left.value.ival + right.value.ival));
                    break;
                }
                if (right.type == DurianType::Double) {
                    m_dataStack.push(DurianObject(left.value.ival + right.value.dval));
                    break;
                }
            }
            if (left.type == DurianType::Double) {
                if (right.type == DurianType::Integer) {
                    m_dataStack.push(DurianObject(left.value.dval + right.value.ival));
                    break;
                }
                if (right.type == DurianType::Double) {
                    m_dataStack.push(DurianObject(left.value.dval + right.value.dval));
                    break;
                }
            }
            // TODO throw exception
            break;
        case TokenType::Minus:
            if (left.type == DurianType::Integer) {
                if (right.type == DurianType::Integer) {
                    m_dataStack.push(DurianObject(left.value.ival - right.value.ival));
                    break;
                }
                if (right.type == DurianType::Double) {
                    m_dataStack.push(DurianObject(left.value.ival - right.value.dval));
                    break;
                }
            }
            if (left.type == DurianType::Double) {
                if (right.type == DurianType::Integer) {
                    m_dataStack.push(DurianObject(left.value.dval - right.value.ival));
                    break;
                }
                if (right.type == DurianType::Double) {
                    m_dataStack.push(DurianObject(left.value.dval - right.value.dval));
                    break;
                }
            }
            // TODO throw exception
            break;
        case TokenType::Star:
            if (left.type == DurianType::Integer) {
                if (right.type == DurianType::Integer) {
                    m_dataStack.push(DurianObject(left.value.ival * right.value.ival));
                    break;
                }
                if (right.type == DurianType::Double) {
                    m_dataStack.push(DurianObject(left.value.ival * right.value.dval));
                    break;
                }
            }
            if (left.type == DurianType::Double) {
                if (right.type == DurianType::Integer) {
                    m_dataStack.push(DurianObject(left.value.dval * right.value.ival));
                    break;
                }
                if (right.type == DurianType::Double) {
                    m_dataStack.push(DurianObject(left.value.dval - right.value.dval));
                    break;
                }
            }
            // TODO throw exception
            break;
        case TokenType::Slash:
            if (left.type == DurianType::Integer) {
                if (right.type == DurianType::Integer) {
                    m_dataStack.push(DurianObject(left.value.ival / right.value.ival));
                    break;
                }
                if (right.type == DurianType::Double) {
                    m_dataStack.push(DurianObject(left.value.ival / right.value.dval));
                }
            }
            if (left.type == DurianType::Double) {
                if (right.type == DurianType::Integer) {
                    m_dataStack.push(DurianObject(left.value.dval / right.value.ival));
                    break;
                }
                if (right.type == DurianType::Double) {
                    m_dataStack.push(DurianObject(left.value.dval / right.value.dval));
                    break;
                }
            }
            // TODO throw exception
            break;
        case TokenType::BangEqual:
            break;
        case TokenType::EqualEqual:
            break;
        case TokenType::Lesser:
            if (left.type == DurianType::Integer) {
                if (right.type == DurianType::Integer) {
                    m_dataStack.push(DurianObject(left.value.ival < right.value.ival));
                    break;
                }
                if (right.type == DurianType::Double) {
                    m_dataStack.push(DurianObject(left.value.ival < right.value.dval));
                    break;
                }
            }
            if (left.type == DurianType::Double) {
                if (right.type == DurianType::Integer) {
                    m_dataStack.push(DurianObject(left.value.dval < right.value.ival));
                    break;
                }
                if (right.type == DurianType::Double) {
                    m_dataStack.push(DurianObject(left.value.dval < right.value.dval));
                    break;
                }
            }
            // TODO throw exception
            break;
        case TokenType::LesserEqual:
            if (left.type == DurianType::Integer) {
                if (right.type == DurianType::Integer) {
                    m_dataStack.push(DurianObject(left.value.ival <= right.value.ival));
                    break;
                }
                if (right.type == DurianType::Double) {
                    m_dataStack.push(DurianObject(left.value.ival <= right.value.dval));
                    break;
                }
            }
            if (left.type == DurianType::Double) {
                if (right.type == DurianType::Integer) {
                    m_dataStack.push(DurianObject(left.value.dval <= right.value.ival));
                    break;
                }
                if (right.type == DurianType::Double) {
                    m_dataStack.push(DurianObject(left.value.dval <= right.value.dval));
                    break;
                }
            }
            // TODO throw exception
            break;
        case TokenType::Greater:
            if (left.type == DurianType::Integer) {
                if (right.type == DurianType::Integer) {
                    m_dataStack.push(DurianObject(left.value.ival > right.value.ival));
                    break;
                }
                if (right.type == DurianType::Double) {
                    m_dataStack.push(DurianObject(left.value.ival > right.value.dval));
                    break;
                }
            }
            if (left.type == DurianType::Double) {
                if (right.type == DurianType::Integer) {
                    m_dataStack.push(DurianObject(left.value.dval > right.value.ival));
                    break;
                }
                if (right.type == DurianType::Double) {
                    m_dataStack.push(DurianObject(left.value.dval > right.value.dval));
                    break;
                }
            }
            // TODO throw exception
            break;
        case TokenType::GreaterEqual:
            if (left.type == DurianType::Integer) {
                if (right.type == DurianType::Integer) {
                    m_dataStack.push(DurianObject(left.value.ival >= right.value.ival));
                    break;
                }
                if (right.type == DurianType::Double) {
                    m_dataStack.push(DurianObject(left.value.ival >= right.value.dval));
                    break;
                }
            }
            if (left.type == DurianType::Double) {
                if (right.type == DurianType::Integer) {
                    m_dataStack.push(DurianObject(left.value.dval >= right.value.ival));
                    break;
                }
                if (right.type == DurianType::Double) {
                    m_dataStack.push(DurianObject(left.value.dval >= right.value.dval));
                    break;
                }
            }
            // TODO throw exception
            break;
        default:
            // TODO throw exception
            break;
    }
}

void Interpreter::visit(AST::BlockStmt *node) {
    auto oldScope = m_currentScope;
    m_currentScope = std::make_shared<Environment>(Environment(oldScope));
    for (auto stmtIter = node->m_statements.begin(); stmtIter != node->m_statements.end(); ++stmtIter) {
        stmtIter->get()->accept(this);
    }
    m_currentScope = oldScope;
}

void Interpreter::visit(AST::BooleanLit *node) {
    m_dataStack.push(DurianObject(node->m_value));
}

void Interpreter::visit(AST::BreakStmt *) {
    throw ControlFlowException(ControlFlowException::Type::Break, DurianObject());
}

void Interpreter::visit(AST::ErrStmt *node) {
    node->m_expr->accept(this);
    if (m_dataStack.top().type != DurianType::String) {
        // TODO throw exception
    }
    std::cerr << m_dataStack.top().value.sval << std::endl;
    m_dataStack.pop();
}

void Interpreter::visit(AST::ExprStmt *node) {
    node->m_expr->accept(this);
    m_dataStack.pop();
}

void Interpreter::visit(AST::FloatLit *node) {
    m_dataStack.push(DurianObject(node->m_value));
}

void Interpreter::visit(AST::FnCall *node) {}

void Interpreter::visit(AST::FnDecl *node) {}

void Interpreter::visit(AST::Identifier *node) {
    m_dataStack.push(m_currentScope->get(node->m_identStr));
}

void Interpreter::visit(AST::IfStmt *node) {
    node->m_condition->accept(this);
    auto val = m_dataStack.top();
    m_dataStack.pop();
    if (val.type != DurianType::Boolean) {
        // TODO throw exception
    }
    if (val.value.bval) {
        node->m_trueBody->accept(this);
    } else {
        if (node->m_falseBody != nullptr) {
            node->m_falseBody->accept(this);
        }
    }
}

void Interpreter::visit(AST::IntegerLit *node) {
    m_dataStack.push(DurianObject(node->m_value));
}

void Interpreter::visit(AST::LetStmt *node) {
    node->m_expr->accept(this);
    const DurianObject val = m_dataStack.top();
    m_dataStack.pop();
    std::shared_ptr<Environment> newScope = std::make_shared<Environment>(Environment(m_currentScope));
    m_currentScope = newScope;
    m_currentScope->declare(node->m_ident->m_identStr, val);
}

void Interpreter::visit(AST::NextStmt *) {
    throw ControlFlowException(ControlFlowException::Type::Next, DurianObject());
}

void Interpreter::visit(AST::PrintStmt *node) {
    node->m_expr->accept(this);
    if (m_dataStack.top().type != DurianType::String) {
        // TODO throw exception
    }
    std::cout << m_dataStack.top().value.sval << std::endl;
    m_dataStack.pop();
}

void Interpreter::visit(AST::ReturnStmt *node) {
    node->m_expr->accept(this);
    auto val = m_dataStack.top();
    m_dataStack.pop();
    throw ControlFlowException(ControlFlowException::Type::Return, val);
}

void Interpreter::visit(AST::ScanStmt *node) {
    node->m_ident->accept(this);
    const DurianObject ident = m_dataStack.top();
    m_dataStack.pop();
    if (ident.type != DurianType::String) {
        // TODO throw exception
    }
    std::string temp;
    std::cin >> temp;
    m_currentScope->assign(std::string(ident.value.sval), DurianObject(temp));
}

void Interpreter::visit(AST::StringLit *node) {
    m_dataStack.push(DurianObject(node->m_value));
}

void Interpreter::visit(AST::UnaryExpr *node) {
    node->m_operand->accept(this);
    const DurianObject operand = m_dataStack.top();
    m_dataStack.pop();
    switch (node->m_op) {
        case TokenType::Plus:
            // TODO
            break;
        case TokenType::Minus:
            // TODO
            break;
        case TokenType::Ampersand:
            // TODO
            break;
        case TokenType::Bang:
            m_dataStack.push(DurianObject(!operand.isTruthy()));
            break;
        default:
            assert(false);
            break;
    }
}

void Interpreter::visit(AST::WhileStmt *node) {
    bool tmp = true;
    while (tmp) {
        node->m_condition->accept(this);
        auto cond = m_dataStack.top();
        m_dataStack.pop();
        if (cond.isTruthy()) {
            try {
                node->m_body->accept(this);
            } catch (const ControlFlowException &e) {
                switch (e.type) {
                    case ControlFlowException::Type::Break:
                        tmp = false;
                        break;
                    case ControlFlowException::Type::Next:
                        continue;
                    case ControlFlowException::Type::Return:
                        throw e;
                }
            }
        } else {
            tmp = false;
        }
    }
}
