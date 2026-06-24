pub mod mutator;
pub mod parser;

use axum::{
    http::{HeaderValue, Method},
    routing::post,
    Json, Router,
};
use serde::{Deserialize, Serialize};
use tower_http::cors::{Any, CorsLayer};

#[derive(Debug, Deserialize)]
struct ParseRequest {
    code: String,
}

#[derive(Debug, Deserialize)]
struct MutateRequest {
    code: String,
    mutation: mutator::Mutation,
}

#[derive(Debug, Serialize)]
struct MutateResponse {
    code: String,
    model: parser::SysmlModel,
}

async fn handle_parse(Json(req): Json<ParseRequest>) -> Json<parser::SysmlModel> {
    let model = parser::parse_sysml(&req.code);
    Json(model)
}

async fn handle_mutate(Json(req): Json<MutateRequest>) -> Json<MutateResponse> {
    let new_code = mutator::apply_mutation(&req.code, req.mutation);
    let model = parser::parse_sysml(&new_code);
    Json(MutateResponse {
        code: new_code,
        model,
    })
}

#[tokio::main]
async fn main() {
    // Setup CORS layer
    let cors = CorsLayer::new()
        .allow_origin(Any)
        .allow_methods([Method::GET, Method::POST, Method::OPTIONS])
        .allow_headers(Any);

    // Build routes
    let app = Router::new()
        .route("/", axum::routing::get(|| async { "OK" }))
        .route("/api/parse", post(handle_parse))
        .route("/api/mutate", post(handle_mutate))
        .layer(cors);

    // Listen on localhost:3000
    let listener = tokio::net::TcpListener::bind("127.0.0.1:3000")
        .await
        .unwrap();
    println!("Backend server running on http://127.0.0.1:3000");
    axum::serve(listener, app).await.unwrap();
}
