/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkiloul <lkiloul@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:10:58 by lkiloul           #+#    #+#             */
/*   Updated: 2025/06/04 11:21:27 by lkiloul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* Forward declarations pour éviter les dépendances circulaires */
typedef struct s_token	t_token;
typedef struct s_env	t_env;

/**
 * Structure représentant une commande avec ses arguments et redirections
 * Cette structure a été étendue pour supporter les redirections
 */
typedef struct s_command
{
	char		**args;				/* Arguments de la commande (argv) */
	t_token		*redirections;		/* Liste des tokens de redirection */
}	t_command;

/**
 * Structure pour le parsing des tokens
 * Utilisée pour séparer les arguments des redirections
 */
typedef struct s_parse_context
{
	int		arg_count;				/* Nombre d'arguments */
	int		redirection_count;		/* Nombre de redirections */
	char	**temp_args;			/* Arguments temporaires */
	t_token	*temp_redirections;		/* Redirections temporaires */
}	t_parse_context;

/* ========================================================================== */
/*                            FONCTIONS DE PARSING                           */
/* ========================================================================== */

/**
 * Fonction principale de parsing d'une ligne de commande
 * @param line La ligne à parser
 * @return Un pointeur vers la commande parsée ou NULL en cas d'erreur
 */
t_command	*parse_line(char *line);

/**
 * Parse une liste de tokens en séparant arguments et redirections
 * @param tokens Liste des tokens à parser
 * @return Une commande avec arguments et redirections séparés
 */
t_command	*parse_tokens_to_command(t_token *tokens);

/**
 * Initialise une nouvelle commande
 * @param arg_count Nombre d'arguments
 * @return Une nouvelle commande initialisée ou NULL en cas d'erreur
 */
int			init_command(t_token *token, t_command **cmd);

/**
 * Copie les arguments dans la structure de commande
 * @param cmd La commande destination
 * @param tokens Liste des tokens source
 * @param arg_count Nombre d'arguments à copier
 * @return 0 en cas de succès, -1 en cas d'erreur
 */

/**
 * Extrait et copie les redirections depuis une liste de tokens
 * @param tokens Liste des tokens source
 * @return Liste des tokens de redirection ou NULL
 */
t_token		*extract_redirections(t_token *tokens);
int			redirect_heredoc(char *filename);
/**
 * Extrait les redirections d'une commande spécifique
 * @param cmd_start Début des tokens de la commande
 * @return Liste des tokens de redirection ou NULL
 */
t_token		*extract_command_redirections(t_token *cmd_start);

/* ========================================================================== */
/*                         FONCTIONS UTILITAIRES                             */
/* ========================================================================== */

/**
 * Compte le nombre d'arguments (non-redirections) dans une liste de tokens
 * @param tokens Liste des tokens
 * @return Nombre d'arguments
 */
int			count_command_args(t_token *tokens);

/**
 * Compte le nombre de redirections dans une liste de tokens
 * @param tokens Liste des tokens
 * @return Nombre de redirections
 */
int			count_redirections(t_token *tokens);

/**
 * Vérifie si un token est une redirection
 * @param token Le token à vérifier
 * @return 1 si c'est une redirection, 0 sinon
 */
int			is_redirection(t_token *token);

/**
 * Vérifie si un token est un pipe
 * @param token Le token à vérifier
 * @return 1 si c'est un pipe, 0 sinon
 */
int			is_pipe_token(t_token *token);

/**
 * Vérifie la syntaxe des redirections
 * @param tokens Liste des tokens à vérifier
 * @return 0 si la syntaxe est correcte, -1 sinon
 */
int			validate_redirection_syntax(t_token *tokens);

/**
 * Vérifie les erreurs de syntaxe dans les tokens
 * @param tokens Liste des tokens à vérifier
 * @return 0 si pas d'erreur, -1 sinon
 */
int			error_token(t_token *tokens);

/* ========================================================================== */
/*                         FONCTIONS DE NETTOYAGE                            */
/* ========================================================================== */

/**
 * Libère une commande et toutes ses ressources
 * @param cmd La commande à libérer
 */
void		free_command(t_command *cmd);

/**
 * Libère un contexte de parsing
 * @param context Le contexte à libérer
 */
void		free_parse_context(t_parse_context *context);

/**
 * Libère une liste de tokens
 * @param tokens La liste à libérer
 */
void		free_token_list(t_token *tokens);

/* ========================================================================== */
/*                           FONCTIONS DE DEBUG                              */
/* ========================================================================== */

/**
 * Affiche une commande pour le debug
 * @param cmd La commande à afficher
 */
void		print_command_debug(t_command *cmd);

/**
 * Affiche une liste de tokens pour le debug
 * @param tokens La liste à afficher
 * @param title Titre pour l'affichage
 */
void		print_tokens_debug(t_token *tokens, char *title);

#endif