/*
 markdown_parser_sections.h     MindForger thinking notebook

 Copyright (C) 2016-2018 Martin Dvorak <martin.dvorak@mindforger.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef M8R_MARKDOWN_PARSER_SECTIONS_H_
#define M8R_MARKDOWN_PARSER_SECTIONS_H_

#include <string>
#include <vector>

// debug
#include <iostream>

#include "../../gear/datetime_utils.h"

#include "markdown_ast_node.h"
#include "markdown_lexer_sections.h"

namespace m8r {

class MarkdownAstNodeSection;
class MarkdownAstSectionMetadata;

/**
 * @brief Markdown recursive-descent parser for section-level granularity AST.
 *
 * OPTIMISTIC Markdown RDP expects syntactically valid input - it can simplify
 * parsing process to ensure reasonable performance it implements minimal
 * robustness.
 */
class MarkdownParserSections
{
private:
    MarkdownLexerSections& lexer;

    std::vector<MarkdownAstNodeSection*>* ast;

public:
    explicit MarkdownParserSections(MarkdownLexerSections& lexer);
    MarkdownParserSections(const MarkdownParserSections&) = delete;
    MarkdownParserSections(const MarkdownParserSections&&);
    MarkdownParserSections &operator=(const MarkdownParserSections&) = delete;
    MarkdownParserSections &operator=(const MarkdownParserSections&&) = delete;
    virtual ~MarkdownParserSections();

    void parse(void);

    std::vector<MarkdownAstNodeSection*>* getAst(void) const { return ast; }
    std::vector<MarkdownAstNodeSection*>* moveAst(void) {
        std::vector<MarkdownAstNodeSection*>* result = ast;
        ast = nullptr;
        return result;
    };
    size_t size(void) const { return ast==nullptr?0:ast->size(); }
    bool empty(void) const { return ast==nullptr?true:ast->empty(); }

private:
    inline const MarkdownLexem* lookahead(size_t offset);
    inline const MarkdownLexem* lookahead(MarkdownLexemType, size_t offset);
    inline const MarkdownLexem* lookaheadNot(MarkdownLexemType, size_t offset);
    inline void skipWhitespaces(size_t& offset);
    inline void skipEOL(size_t& offset);
    inline void skipSectionBody(size_t& offset);

    void markdownRule(void);
    MarkdownAstNodeSection* sectionRule(size_t& offset);
    MarkdownAstNodeSection* sectionHeaderRule(size_t& offset);
    std::string* sectionTitleRule(size_t& offset);
    bool sectionMetadataRule(MarkdownAstSectionMetadata& meta, size_t& offset);
    const MarkdownLexem* parsePropertyValue(size_t& offset);
    time_t parsePropertyValueTimestamp(size_t& offset);
    int parsePropertyValueInteger(size_t& offset);
    int parsePropertyValueFraction(size_t& offset);
    int parsePropertyValuePercent(size_t& offset);
    std::string* parsePropertyValueString(size_t& offset);
    std::vector<std::string*>* parsePropertyValueTags(size_t& offset);
    std::vector<std::string*>* sectionBodyRule(size_t& offset);
    void skipBr(size_t& offset);
};

} /* namespace m8r */

#endif /* M8R_MARKDOWN_PARSER_SECTIONS_H_ */